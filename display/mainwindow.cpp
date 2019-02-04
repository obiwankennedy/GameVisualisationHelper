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

    // 13eme légion
    m_model->addPerson(new Character(QStringLiteral("Isawa Yasuhiro"), QStringLiteral("Chewba"),
        QStringLiteral("qrc:/resources/l5rTibo/Shiba_Yasuhiro.jpg"), QStringLiteral("13eme"), QColor(Qt::red)));

    m_model->addPerson(new Character(QStringLiteral("Hida Kyonyu"), QStringLiteral("Capitaine Red"),
        QStringLiteral("qrc:/resources/l5rTibo/Hida_Kyonyu.jpg"), QStringLiteral("13eme"), QColor(Qt::darkBlue)));

    m_model->addPerson(new Character(QStringLiteral("Ikoma Kae"), QStringLiteral("Obi"),
        QStringLiteral("qrc:/resources/l5rTibo/Ikoma_Kae.jpg"), QStringLiteral("13eme"), QColor("#9C9C00")));

    m_model->addPerson(new Character(QStringLiteral("Togashi Sento"), QStringLiteral("Beskargam"),
        QStringLiteral("qrc:/resources/l5rTibo/Togashi_Sento.jpg"), QStringLiteral("13eme"), QColor(Qt::darkGreen)));

    m_model->addPerson(new Character(QStringLiteral("Alci (MJ)"), QStringLiteral("Alci"),
        QStringLiteral("qrc:/resources/l5rTibo/MJ.jpg"), QStringLiteral("13eme"), QColor(Qt::darkMagenta)));

    // COPS
    m_model->addPerson(new Character(QStringLiteral("Lynn Gray-Rike"), QStringLiteral("Obi"),
        QStringLiteral("qrc:/resources/Cops/Lynn_Gray-Rike.png"), QStringLiteral("COPS"), QColor("#003B8C")));

    m_model->addPerson(new Character(QStringLiteral("Juan Ramirez"), QStringLiteral("TlonUqbar"),
        QStringLiteral("qrc:/resources/Cops/Guillermo_Gonzalvez.png"), QStringLiteral("COPS"), QColor(Qt::darkGreen)));

    m_model->addPerson(new Character(QStringLiteral("Max O'Hara"), QStringLiteral("Chewba"),
        QStringLiteral("qrc:/resources/Cops/max_ohara_bis.jpg"), QStringLiteral("COPS"), QColor(Qt::red)));

    m_model->addPerson(new Character(QStringLiteral("Denis Aquillian"), QStringLiteral("Wedge"),
        QStringLiteral("qrc:/resources/Cops/Denis_Aquillian.png"), QStringLiteral("COPS"), QColor("#CE5C00")));

    m_model->addPerson(new Character(QStringLiteral("Scott J. Spann"), QStringLiteral("Alci"),
        QStringLiteral("qrc:/resources/Cops/Rob-Mills-head-shot.jpg"), QStringLiteral("COPS"), QColor(Qt::darkCyan)));

    m_model->addPerson(new Character(QStringLiteral("MJ"), QStringLiteral("kromisback"),
        QStringLiteral("qrc:/resources/Cops/mj.png"), QStringLiteral("COPS"), QColor(Qt::darkBlue)));

    // Warhammer
    m_model->addPerson(new Character(QStringLiteral("Dornthal"), QStringLiteral("Obi"),
        QStringLiteral("qrc:/resources/warhammer/out/Dornthal.jpg"), QStringLiteral("Warhammer"), QColor("#087D1D")));

    m_model->addPerson(new Character(QStringLiteral("Beatrix"), QStringLiteral("TlonUqbar"),
        QStringLiteral("qrc:/resources/warhammer/out/Beatrix_Buchwald.jpg"), QStringLiteral("Warhammer"),
        QColor("#7e4640")));

    m_model->addPerson(new Character(QStringLiteral("Hoeneïm"), QStringLiteral("SombreLune"),
        QStringLiteral("qrc:/resources/warhammer/out/Hoeneïm_Raynster.png"), QStringLiteral("Warhammer"),
        QColor(Qt::lightGray)));

    m_model->addPerson(new Character(QStringLiteral("Kranich"), QStringLiteral("Wedge"),
        QStringLiteral("qrc:/resources/warhammer/out/Kranich_Vogel.jpg"), QStringLiteral("Warhammer"),
        QColor(Qt::red)));

    m_model->addPerson(new Character(QStringLiteral("Sepp Breuer"), QStringLiteral("kromisback"),
        QStringLiteral("qrc:/resources/warhammer/out/Sepp_Breuer.jpg"), QStringLiteral("Warhammer"),
        QColor(Qt::darkBlue)));

    m_model->addPerson(new Character(QStringLiteral("Squirrel (MJ)"), QStringLiteral("Squirrel"),
        QStringLiteral("qrc:/resources/warhammer/out/KeA.jpg"), QStringLiteral("Warhammer"), QColor("#CE5C00")));

    // OneShot
    m_model->addPerson(new Character(QStringLiteral("Obi (MJ)"), QStringLiteral("Obi"),
        QStringLiteral("qrc:/resources/OneShotGeneral/predateur.jpg"), QStringLiteral("OneShot"), QColor(Qt::red)));

    m_model->addPerson(new Character(QStringLiteral("TlonUqbar"), QStringLiteral("TlonUqbar"),
        QStringLiteral("qrc:/resources/OneShotGeneral/tlon.jpg"), QStringLiteral("OneShot"), QColor("#7e4640")));

    m_model->addPerson(new Character(QStringLiteral("SombreLune"), QStringLiteral("SombreLune"), QStringLiteral(""),
        QStringLiteral("OneShot"), QColor(Qt::lightGray)));

    m_model->addPerson(new Character(QStringLiteral("Wedge"), QStringLiteral("Wedge"), QStringLiteral(""),
        QStringLiteral("OneShot"), QColor(Qt::red)));

    m_model->addPerson(new Character(QStringLiteral("Capitaine Red"), QStringLiteral("Capitaine Red"),
        QStringLiteral("qrc:/resources/l5rTibo/Hida_Kyonyu.jpg"), QStringLiteral("OneShot"), QColor(Qt::darkBlue)));

    m_model->addPerson(new Character(QStringLiteral("Alci"), QStringLiteral("Alci"),
        QStringLiteral("qrc:/resources/OneShotGeneral/alci.jpg"), QStringLiteral("OneShot"), QColor(Qt::darkCyan)));

    m_model->addPerson(new Character(QStringLiteral("Chewba"), QStringLiteral("Chewba"),
        QStringLiteral("qrc:/resources/OneShotGeneral/chewb.jpg"), QStringLiteral("OneShot"), QColor(Qt::darkGreen)));

    m_model->addPerson(new Character(QStringLiteral("kromisback"), QStringLiteral("kromisback"),
        QStringLiteral("qrc:/resources/OneShotGeneral/krom.jpg"), QStringLiteral("OneShot"), QColor(Qt::darkBlue)));

    m_model->addPerson(new Character(QStringLiteral("Squirrel (MJ)"), QStringLiteral("Squirrel"), QStringLiteral(""),
        QStringLiteral("OneShot"), QColor("#CE5C00")));

    // SOMBRE
    m_model->addPerson(new Character(QStringLiteral("John Mc Cain"), QStringLiteral("Akima"),
        QStringLiteral("http://tomcatsite.pagesperso-orange.fr/images/agence%20risque/images/colonel_jpg.jpg"),
        QStringLiteral("SOMBRE"), QColor(Qt::darkBlue)));

    m_model->addPerson(new Character(QStringLiteral("Keith Wagner"), QStringLiteral("Akima"),
        QStringLiteral("http://imgix.ranker.com/user_node_img/41/806932/original/"
                       "damian-lewis-theater-actors-photo-u6?w=280&h=280&fit=crop&crop=faces&q=50&fmt=jpg"),
        QStringLiteral("SOMBRE"), QColor(Qt::darkCyan)));

    m_model->addPerson(new Character(QStringLiteral("Steve Works"), QStringLiteral("SombreLune"),
        QStringLiteral("qrc:/resources/OneShotGeneral/chewb.jpg"), QStringLiteral("SOMBRE"), QColor(Qt::darkGreen)));

    m_model->addPerson(new Character(QStringLiteral("kromisback"), QStringLiteral("kromisback"),
        QStringLiteral("qrc:/resources/OneShotGeneral/krom.jpg"), QStringLiteral("SOMBRE"), QColor(Qt::darkBlue)));

    m_model->addPerson(new Character(QStringLiteral("Cyril Panouna"), QStringLiteral("Amakiir"),
        QStringLiteral("http://cdn.programme-television.org/var/premiere/storage/images/tele-7-jours/news-tv/"
                       "said-taghmaoui-rejoint-la-serie-legion-inspiree-des-x-men-4510946/91476062-1-fre-FR/"
                       "Said-Taghmaoui-rejoint-la-serie-Legion-inspiree-des-X-Men_news_full.jpg"),
        QStringLiteral("SOMBRE"), QColor("#CE5C00")));

    m_model->addPerson(new Character(QStringLiteral("Micheal O'Malley"), QStringLiteral("Xenorius"),
        QStringLiteral("http://i.imgur.com/rCpydBL.png"), QStringLiteral("SOMBRE"), QColor("#7e4640")));
    // end of sombre

    QStringList camp;
    camp << "Warhammer"
         << "COPS"
         << "13eme"
         << "OneShot"
         << "SOMBRE";
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
    auto today= QDate::currentDate();
    QString currentCampaign= "OneShot";
    if(today.dayOfWeek() == 1) // monday
    {
        currentCampaign= "COPS";
    }
    else if(today.dayOfWeek() == 2)
    {
        currentCampaign= "Warhammer";
    }
    else if(today.dayOfWeek() == 3)
    {
        currentCampaign= "13eme";
    }
    else if(today.dayOfWeek() == 5)
    {
        currentCampaign= "OneShot";
    }
    m_proxyModel->setCurrentCampaign(currentCampaign);
    m_selectModel->setCurrentCampaign(currentCampaign);
    ui->comboBox->setCurrentText(currentCampaign);

    refreshQMLEngine();
}

MainWindow::~MainWindow() {}

void MainWindow::refreshQMLEngine()
{
    m_engine.reset(new QQmlApplicationEngine());
    m_engine->rootContext()->setContextProperty("_model", m_proxyModel);

    m_engine->load(QUrl("qrc:/qml/main.qml"));
    setAttribute(Qt::WA_DeleteOnClose, true);
}

void MainWindow::displayCorrectImage(QString user)
{
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
