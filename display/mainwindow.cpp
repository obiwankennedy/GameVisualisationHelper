/***************************************************************************
 *   Copyright (C) 2015 by Renaud Guezennec                                *
 *   http://renaudguezennec.homelinux.org/accueil,3.html                   *
 *                                                                         *
 *   rolisteam is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDate>
#include <QDebug>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTimer>

#include "character.h"
#include "characteravatarmodel.h"
#include "presentproxymodel.h"

#include <QQmlContext>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    // Init data
    m_model= new CharacterAvatarModel(this);

    // Loup garou
    m_model->addPerson(new Character(QStringLiteral("Bidouille"), QStringLiteral("Chewba"),
                                     QStringLiteral("qrc:/resources/lg/chewb.png"), QStringLiteral("jeudi"),
                                     QColor(Qt::red), "_chewba"));

    m_model->addPerson(new Character(QStringLiteral("Shade"), QStringLiteral("Xelal"),
                                     QStringLiteral("qrc:/resources/lg/xelal.jpg"), QStringLiteral("jeudi"),
                                     QColor(Qt::green), "_xelal"));

    m_model->addPerson(new Character(QStringLiteral("Capitaine Red"), QStringLiteral("Capitaine Red"),
                                     QStringLiteral("qrc:/resources/lg/captain.jpg"), QStringLiteral("jeudi"),
                                     QColor(Qt::darkBlue), "_captain"));

    m_model->addPerson(new Character(QStringLiteral("Obi (MJ)"), QStringLiteral("Obi"),
                                     QStringLiteral("qrc:/resources/OneShotGeneral/predateur.jpg"),
                                     QStringLiteral("jeudi"), QColor("#9C9C00"), "_obi"));

    m_model->addPerson(new Character(QStringLiteral("Goupille"), QStringLiteral("Alci"),
                                     QStringLiteral("qrc:/resources/lg/alci.jpg"), QStringLiteral("jeudi"),
                                     QColor(Qt::darkMagenta), "_alci"));

    QStringList camp;
    camp << "jeudi";
    ui->comboBox->addItems(camp);

    m_selectModel= new SelectPresentProxyModel(this);

    connect(ui->actionSave_As, &QAction::triggered, this, [this]() { saveFile(true); });
    connect(ui->actionSave, &QAction::triggered, this, [this]() { saveFile(false); });
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::loadFile);

    m_proxyModel= new PresentProxyModel(this);
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, [=](QString str) {
        m_proxyModel->setCurrentCampaign(str);
        m_selectModel->setCurrentCampaign(str);
    });
    connect(m_selectModel, &SelectPresentProxyModel::selectionChanged, this,
            [=]() { m_proxyModel->setHiddenPeople(m_selectModel->hiddenPeople()); });

    m_proxyModel->setSourceModel(m_model);
    m_selectModel->setSourceModel(m_model);
    ui->m_presentList->setModel(m_selectModel);

    ui->m_characterView->setModel(m_proxyModel);
    auto currentCampaign= "jeudi";

    m_proxyModel->setCurrentCampaign(currentCampaign);
    m_selectModel->setCurrentCampaign(currentCampaign);
    ui->comboBox->setCurrentText(currentCampaign);

    refreshQMLEngine();
}

MainWindow::~MainWindow() {}

void MainWindow::refreshQMLEngine()
{
    m_engine.reset(new QQmlApplicationEngine());

    auto chars= m_model->characters();
    for(auto pers : chars)
    {
        m_engine->rootContext()->setContextProperty(pers->id(), pers);
    }

    m_engine->rootContext()->setContextProperty("_model", m_proxyModel);

    m_engine->load(QUrl("qrc:/qml/main.qml"));
    setAttribute(Qt::WA_DeleteOnClose, true);
}

void MainWindow::displayCorrectImage(QString user)
{
    if(user.compare("obi1", Qt::CaseInsensitive))
        return;

    m_model->speakingStatusChanged(user, true);
    if(!m_timeTotalByUser.contains(user))
    {
        m_timeTotalByUser.insert(user, new QTime());
    }

    QTime* time= m_timeTotalByUser.value(user);
    time->start();
}
void MainWindow::hideImage(QString user)
{
    if(user.compare("obi1", Qt::CaseInsensitive))
        return;

    m_model->speakingStatusChanged(user, false);
    if(m_timeTotalByUser.contains(user))
    {
        quint64 mili= m_timeTotalByUser.value(user)->elapsed();

        qreal time= (qreal)mili / 1000.0;
        if(m_cumulTimeByUser.contains(user))
        {
            m_cumulTimeByUser[user]+= time;
        }
        else
        {
            m_cumulTimeByUser.insert(user, time);
        }

        if(m_model->maxSpeakingTime() < m_cumulTimeByUser[user])
        {
            m_model->setMaxSpeakingTime(m_cumulTimeByUser[user]);
        }
        m_model->setSpeakingTimeForUser(user, ui->comboBox->currentText(), m_cumulTimeByUser[user]);
    }
}

void MainWindow::loadFile()
{
    QString filename
        = QFileDialog::getOpenFileName(this, tr("Load file"), QDir::homePath(), "Character Base (*.cdb *.json)");
    if(filename.isEmpty())
        return;

    m_filename= filename;

    QFile file(m_filename);
    file.open(QIODevice::ReadOnly);
    QJsonDocument doc= QJsonDocument::fromJson(file.readAll());
    auto array= doc.array();
    m_model->readData(array);
}

void MainWindow::saveFile(bool saveAs)
{
    if(saveAs || m_filename.isEmpty())
    {
        QString filename
            = QFileDialog::getSaveFileName(this, tr("Save file"), QDir::homePath(), "Character Base (*.cdb *.json)");
        if(filename.isEmpty())
            return;
        m_filename= filename;
    }

    QJsonDocument doc;
    QJsonArray array;
    m_model->writeData(array);
    doc.setArray(array);
    QFile file(m_filename);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());
}
void MainWindow::resizeEvent(QResizeEvent* ev)
{
    QMainWindow::resizeEvent(ev);
}
bool MainWindow::maybeSave()
{
    return true;
}
void MainWindow::closeEvent(QCloseEvent* event)
{
    if(maybeSave())
    {
        qDebug() << "delete mainwindow" << m_cumulTimeByUser.size();
        for(auto keyItem : m_cumulTimeByUser.keys())
        {
            qDebug() << keyItem << ":" << m_cumulTimeByUser.value(keyItem);
        }
        // saveFile(false);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::on_actionRefresh_triggered()
{
    refreshQMLEngine();
}

void MainWindow::on_actionErase_Time_triggered()
{
    for(auto it= m_cumulTimeByUser.begin(); it != m_cumulTimeByUser.end(); ++it)
    {
        it.value()= 0;
    }
}
