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

#include <QDebug>
#include <QDate>

#include "character.h"
#include "characteravatarmodel.h"
#include "presentproxymodel.h"

#include <QQmlContext>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint );
    connect(ui->actionYoung,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));



    //Init data
    m_model = new CharacterAvatarModel();


    // 13eme légion
    m_model->addPerson(new Character(QStringLiteral("Shiba Yasuhiro"),
                                     QStringLiteral("Chewba"),
                                     QStringLiteral("qrc:/resources/l5rTibo/Shiba_Yasuhiro.jpg"),
                                     QStringLiteral("13eme"),
                                     QColor(Qt::red)));

    m_model->addPerson(new Character(QStringLiteral("Hida Kyonyu"),
                                     QStringLiteral("Capitaine Red"),
                                     QStringLiteral("qrc:/resources/l5rTibo/Hida_Kyonyu.jpg"),
                                     QStringLiteral("13eme"),
                                     QColor(Qt::darkBlue)));

    m_model->addPerson(new Character(QStringLiteral("Ikoma Kae"),
                                     QStringLiteral("Obi"),
                                     QStringLiteral("qrc:/resources/l5rTibo/Ikoma_Kae.jpg"),
                                     QStringLiteral("13eme"),
                                     QColor("#9C9C00")));

    m_model->addPerson(new Character(QStringLiteral("Togashi Sento"),
                                     QStringLiteral("Beskargam"),
                                     QStringLiteral("qrc:/resources/l5rTibo/Togashi_Sento.jpg"),
                                     QStringLiteral("13eme"),
                                     QColor(Qt::darkGreen)));

    m_model->addPerson(new Character(QStringLiteral("Alci (MJ)"),
                                     QStringLiteral("Alci"),
                                     QStringLiteral("qrc:/resources/l5rTibo/MJ.jpg"),
                                     QStringLiteral("13eme"),
                                     QColor(Qt::darkMagenta)));

    // COPS
    m_model->addPerson(new Character(QStringLiteral("Lynn Gray-Rike"),
                                     QStringLiteral("Obi"),
                                     QStringLiteral("qrc:/resources/Cops/Lynn_Gray-Rike.png"),
                                     QStringLiteral("COPS"),
                                     QColor("#003B8C")));

    m_model->addPerson(new Character(QStringLiteral("Guillermo Gonzalvez"),
                                     QStringLiteral("TlonUqbar"),
                                     QStringLiteral("qrc:/resources/Cops/Guillermo_Gonzalvez.png"),
                                     QStringLiteral("COPS"),
                                     QColor(Qt::darkGreen)));

    m_model->addPerson(new Character(QStringLiteral("Max O'Hara"),
                                     QStringLiteral("Chewba"),
                                     QStringLiteral("qrc:/resources/Cops/max_ohara_bis.jpg"),
                                     QStringLiteral("COPS"),
                                     QColor(Qt::red)));

    m_model->addPerson(new Character(QStringLiteral("Denis Aquillian"),
                                     QStringLiteral("Wedge"),
                                     QStringLiteral("qrc:/resources/Cops/Denis_Aquillian.png"),
                                     QStringLiteral("COPS"),
                                     QColor("#CE5C00")));

    m_model->addPerson(new Character(QStringLiteral("MJ"),
                                     QStringLiteral("kromisback"),
                                     QStringLiteral("qrc:/resources/Cops/mj.png"),
                                     QStringLiteral("COPS"),
                                     QColor(Qt::darkBlue)));



    //Warhammer
    m_model->addPerson(new Character(QStringLiteral("Dornthal"),
                                     QStringLiteral("Obi"),
                                     QStringLiteral("qrc:/resources/warhammer/out/Dornthal.jpg"),
                                     QStringLiteral("Warhammer"),
                                     QColor("#087D1D")));

    m_model->addPerson(new Character(QStringLiteral("Beatrix"),
                                     QStringLiteral("TlonUqbar"),
                                     QStringLiteral("qrc:/resources/warhammer/out/Beatrix_Buchwald.jpg"),
                                     QStringLiteral("Warhammer"),
                                     QColor("#7e4640")));

    m_model->addPerson(new Character(QStringLiteral("Hoeneïm"),
                                     QStringLiteral("SombreLune"),
                                     QStringLiteral("qrc:/resources/warhammer/out/Hoeneïm_Raynster.png"),
                                     QStringLiteral("Warhammer"),
                                     QColor(Qt::lightGray)));

    m_model->addPerson(new Character(QStringLiteral("Kranich"),
                                     QStringLiteral("Wedge"),
                                     QStringLiteral("qrc:/resources/warhammer/out/Kranich_Vogel.jpg"),
                                     QStringLiteral("Warhammer"),
                                     QColor(Qt::red)));

    m_model->addPerson(new Character(QStringLiteral("Sepp Breuer"),
                                     QStringLiteral("kromisback"),
                                     QStringLiteral("qrc:/resources/warhammer/out/Sepp_Breuer.jpg"),
                                     QStringLiteral("Warhammer"),
                                     QColor(Qt::darkBlue)));

    m_model->addPerson(new Character(QStringLiteral("Squirrel (MJ)"),
                                     QStringLiteral("Squirrel"),
                                     QStringLiteral("qrc:/resources/warhammer/out/KeA.jpg"),
                                     QStringLiteral("Warhammer"),
                                     QColor("#CE5C00")));

    QStringList camp;
    camp << "Warhammer" << "COPS" << "13eme";
    ui->comboBox->addItems(camp);



    m_selectModel = new SelectPresentProxyModel();




    m_proxyModel = new PresentProxyModel();
    connect(ui->comboBox,&QComboBox::currentTextChanged,this,[=](QString str){
        m_proxyModel->setCurrentCampaign(str);
        m_selectModel->setCurrentCampaign(str);
    });
    connect(m_selectModel,&SelectPresentProxyModel::selectionChanged,this,[=](){
        m_proxyModel->setHiddenPeople(m_selectModel->list());
    });

    m_proxyModel->setSourceModel(m_model);
    m_selectModel->setSourceModel(m_model);
    ui->m_presentList->setModel(m_selectModel);

    ui->m_characterView->setModel(m_proxyModel);
    m_proxyModel->setCurrentCampaign("Warhammer");
    m_selectModel->setCurrentCampaign("Warhammer");

    m_engine = new QQmlApplicationEngine();
    m_engine->rootContext()->setContextProperty("_model",m_proxyModel);

    m_engine->load(QUrl("qrc:/qml/main.qml"));

}

MainWindow::~MainWindow()
{
    for(auto keyItem : m_cumulTimeByUser.keys())
    {
        qDebug() << keyItem <<":"<<m_cumulTimeByUser.value(keyItem) ;
    }
    delete ui;
}
void MainWindow::displayCorrectImage(QString user)
{
    m_model->speakingStatusChanged(user,true);
    if(m_timeTotalByUser.contains(user))
    {
        QTime* time = m_timeTotalByUser.value(user);
        time->start();
    }
}
void MainWindow::hideImage(QString user)
{
    m_model->speakingStatusChanged(user,false);
    if(m_timeTotalByUser.contains(user))
    {
        quint64 mili = m_timeTotalByUser.value(user)->elapsed();

        qreal time = (qreal)mili/1000.0;
        if(m_cumulTimeByUser.contains(user))
        {
            m_cumulTimeByUser[user]+=time;
        }
        else
        {
            m_cumulTimeByUser.insert(user,time);
        }
    }
}
void MainWindow::setImageInLabel()
{

}
void MainWindow::resizeEvent(QResizeEvent * ev)
{
    QMainWindow::resizeEvent(ev);
    setImageInLabel();
}
