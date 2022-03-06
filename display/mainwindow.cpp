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
#include "maincontroller.h"
#include "presentproxymodel.h"

#include <QQmlContext>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), m_ctrl(new MainController)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    QStringList camp;
    camp << "jeudi";
    ui->comboBox->addItems(camp);

    m_filename= m_ctrl->table1() ? "/home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/15_riz/table1.cdb" :
                                   "/home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/15_riz/table2.cdb";

    connect(ui->actionSave_As, &QAction::triggered, this, [this]() { saveFile(true); });
    connect(ui->actionSave, &QAction::triggered, this, [this]() { saveFile(false); });
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::loadFile);

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, [this](QString str) { m_ctrl->setCampaign(str); });

    ui->m_presentList->setModel(m_ctrl->selectModel());

    ui->m_characterView->setModel(m_ctrl->proxyModel());
    auto currentCampaign= "jeudi";

    m_ctrl->setCampaign(currentCampaign);
    ui->comboBox->setCurrentText(currentCampaign);

    refreshQMLEngine();

    loadFile();
}

MainWindow::~MainWindow() {}

void MainWindow::refreshQMLEngine()
{
    m_engine.reset(new QQmlApplicationEngine());

    qmlRegisterSingletonInstance<MainController>("Controller", 1, 0, "MainController", m_ctrl.get());

    /*auto chars= m_model->characters();
    for(auto pers : chars)
    {
        m_engine->rootContext()->setContextProperty(pers->id(), pers);
    }

    m_engine->rootContext()->setContextProperty("_model", m_proxyModel);
    m_engine->rootContext()->setContextProperty("_mainModel", m_model);*/

    m_engine->load(QUrl("qrc:/qml/main.qml"));
    setAttribute(Qt::WA_DeleteOnClose, true);
}

void MainWindow::displayCorrectImage(QString user)
{
    if(user.compare("obi1", Qt::CaseInsensitive) == 0)
        return;

    m_ctrl->avatarModel()->speakingStatusChanged(user, true);
    if(!m_timeTotalByUser.contains(user))
    {
        m_timeTotalByUser.insert(user, new QElapsedTimer());
    }

    QElapsedTimer* time= m_timeTotalByUser.value(user);
    time->start();
}
void MainWindow::hideImage(QString user)
{
    if(user.compare("obi1", Qt::CaseInsensitive) == 0)
        return;

    m_ctrl->avatarModel()->speakingStatusChanged(user, false);
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

        if(m_ctrl->avatarModel()->maxSpeakingTime() < m_cumulTimeByUser[user])
        {
            m_ctrl->avatarModel()->setMaxSpeakingTime(m_cumulTimeByUser[user]);
        }
        m_ctrl->avatarModel()->setSpeakingTimeForUser(user, ui->comboBox->currentText(), m_cumulTimeByUser[user]);
    }
}

void MainWindow::loadFile()
{
    if(m_filename.isEmpty())
    {
        QString filename
            = QFileDialog::getOpenFileName(this, tr("Load file"), QDir::homePath(), "Character Base (*.cdb *.json)");
        if(filename.isEmpty())
            return;

        m_filename= filename;
    }

    QFile file(m_filename);
    file.open(QIODevice::ReadOnly);
    QJsonDocument doc= QJsonDocument::fromJson(file.readAll());
    auto array= doc.array();
    m_ctrl->avatarModel()->readData(array);
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
    m_ctrl->avatarModel()->writeData(array);
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
        for(const auto& keyItem : m_cumulTimeByUser.keys())
        {
            qDebug() << keyItem << ":" << m_cumulTimeByUser.value(keyItem);
        }
        saveFile(false);
        event->accept();
    }
    else
    {
        event->ignore();
    }
    qApp->quit();
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
