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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_numberOfActiveTime=0;
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint );
    connect(ui->actionYoung,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));

    QString str="L5R";
    if(QDate::currentDate().dayOfWeek() == 1 )//monday
    {
        ui->actionCops->setChecked(true);
        str="COPS";
    }
    else if(QDate::currentDate().dayOfWeek() == 3 )//wednesday
    {
        //ui->m_13legion->setChecked(true);
        //str="L5R - La 13ème Légion";

        ui->m_secondeCite->setChecked(true);
        str="L5R - Seconde Cité Saison 2";
    }
    else if(QDate::currentDate().dayOfWeek() == 4)
    {
        ui->m_warhammerAct->setChecked(true);
        str="Warhammer - Campagne Impériale";
    }


    //m_youngMap.insert("Frah",":/resources/Asako.jpg");
    //m_map.insert("Frah",":/resources/Tsuruchi_Nayu.jpg");
    //m_widgetMap.insert("Frah",ui->m_labelTsuruchi);

    connect(ui->m_framelessAct,SIGNAL(triggered()),this,SLOT(setFrameLess()));
    connect(ui->actionCops,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));
    connect(ui->actionCats,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));
    connect(ui->m_oneshotAct,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));
    connect(ui->m_13legion,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));
    connect(ui->m_lgIrlAct,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));
    connect(ui->m_secondeCite,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));


    //Second City
    m_map.insert("Akodo Eiichi",":/resources/Akodo_Eiichi.png");
    m_map.insert("Capitaine Red",":/resources/Shinjo_Zhia.jpg");
    m_map.insert("Chewba",":/resources/Bayushi_Takayoshi.png");
    m_map.insert("Obi",":/resources/mj.jpg");

    m_keyL5rOrder<< "Akodo Eiichi" << "Capitaine Red" << "Chewba" << "Obi"  ;


    ///CATs
    m_catsMap.insert("Leia Tortoise",":/resources/cats/arsene2.jpg");
    //m_catsMap.insert("Gilgamesh",":/resources/cats/Ghandi.jpg");
    m_catsMap.insert("HyiHyil",":/resources/cats/Hercule.jpg");
    m_catsMap.insert("Gilgamesh",":/resources/cats/Sherlock.jpg");
    m_catsMap.insert("Selawyr",":/resources/cats/tatcher.jpg");
    m_catsMap.insert("Obi",":/resources/cats/Matou_Jovial.jpg");

    m_keyCatsOrder << "HyiHyil" << "Leia Tortoise" << "Selawyr" <<  "Gilgamesh" << "Obi";


    /// 13 Légions
    m_map13Legion.insert("Alci",":/resources/l5rTibo/MJ.jpg");
    m_map13Legion.insert("Capitaine Red",":/resources/l5rTibo/Hida_Kyonyu.jpg");
    m_map13Legion.insert("Obi",":/resources/l5rTibo/Ikoma_Kae.jpg");
    m_map13Legion.insert("Chewba",":/resources/l5rTibo/Shiba_Yasuhiro.jpg");
    m_map13Legion.insert("Beskargam",":/resources/l5rTibo/Togashi_Sento.jpg");

    m_key13LegionOrder << "Chewba" << "Capitaine Red" << "Obi" << "Beskar'gam"  << "Alci" ;

    /// Lg IRL
    m_lgIrlLegion.insert("Alci",":/resources/lgIrl/Claudia_Strauss.jpg");
    m_lgIrlLegion.insert("Capitaine Red",":/resources/lgIrl/Ludovic_Clain.jpg");
    m_lgIrlLegion.insert("Obi",":/resources/lgIrl/MJ.jpg");
    //m_lgIrlLegion.insert("Chewba",":/resources/l5rTibo/Shiba_Yasuhiro.jpg");
    m_lgIrlLegion.insert("Beskargam",":/resources/lgIrl/Ruth_Sullivan.jpg");

    m_keyLgIrlOrder << "Capitaine Red" << "Beskargam"  << "Alci" << "Obi";

    ///YOUNG
    m_youngMap.insert("Akodo Eiichi",":/resources/kakita.jpg");
    m_youngMap.insert("Capitaine Red",":/resources/Isawa.jpg");
    m_youngMap.insert("Chewba",":/resources/kitsuki.jpg");
    m_youngMap.insert("Obi",":/resources/mj.jpg");

    m_keyYoungOrder << "Akodo Eiichi" << "Capitaine Red" << "Chewba" << "Obi"  ;



    ///Seconde City saison 2
    m_secondeCityS2Map.insert("Alci",":/resources/sc2saison/out/Shosuro_Ryûu.jpg");
    m_secondeCityS2Map.insert("Capitaine Red",":/resources/sc2saison/out/Shusuro_Shiemi.jpg");
    m_secondeCityS2Map.insert("Chewba",":/resources/sc2saison/out/Soshi_Akimitsu.jpg");
   // m_secondeCityS2Map.insert("Beskargam",":/resources/sc2saison/out/Soshi_Akimitsu.jpg"); //<< "Beskargam"
    m_secondeCityS2Map.insert("Obi",":/resources/mj.jpg");

    m_secondeCityS2Order << "Alci" << "Capitaine Red"  << "Chewba"  << "Obi";


    ///// ONESHOT L5R
    m_l5rOneshotMap.insert("TlonUqbar",":/resources/oneshotFreaks/out/Lilly_Claudel.jpg");
    m_l5rOneshotMap.insert("kromisback",":/resources/oneshotFreaks/out/MJ_.jpg");
    m_l5rOneshotMap.insert("Wedge",":/resources/oneshotFreaks/out/Hikaru_Ichijo.jpg");
    m_l5rOneshotMap.insert("Obi",":/resources/oneshotFreaks/out/Renan_Charbonnier.jpg");

    //m_keyL5rOneshotOrder << "anaisurprise"<< "Flow0333"<< "Wedge"<< "brice" << "pseudo6"<< "Natsu*"<< "Ciennte"<< "Obi";
    m_keyL5rOneshotOrder << "Obi" << "Wedge" << "TlonUqbar" << "kromisback";

    //COPS
    m_copsMap.insert("TlonUqbar",":/resources/Cops/Guillermo_Gonzalvez.png");
    m_copsMap.insert("Chewba",":/resources/Cops/max_ohara_bis.jpg");
    //m_copsMap.insert("Squirrel",":/resources/Cops/Daniel_Mark.png");
    //m_copsMap.insert("Cyb",":/resources/Cops/Rick_Darcy.png");
    m_copsMap.insert("Obi",":/resources/Cops/Lynn_Gray-Rike.png");
    m_copsMap.insert("Wedge",":/resources/Cops/Denis_Aquillian.png");
    //m_copsMap.insert("Cocoon",":/resources/Cops/Christopher_Atkins.jpg");
    m_copsMap.insert("kromisback",":/resources/Cops/mj.png");

    m_keyCopOrder  << "Obi" << "TlonUqbar" << "Chewba"<< "Wedge"<< "kromisback";


    //Warhammer
    m_warHammerMap.insert("TlonUqbar",":/resources/warhammer/out/Beatrix_Buchwald.jpg");
    m_warHammerMap.insert("Squirrel",":/resources/warhammer/out/KeA.jpg");
    m_warHammerMap.insert("Obi",":/resources/warhammer/out/Dornthal.jpg");
    m_warHammerMap.insert("Wedge",":/resources/warhammer/out/Kranich_Vogel.jpg");
    m_warHammerMap.insert("kromisback",":/resources/warhammer/out/Sepp_Breuer.jpg");
    m_warHammerMap.insert("SombreLune",":/resources/warhammer/out/Hoeneïm_Raynster.png");

    m_warHammerOrder  << "Obi" << "TlonUqbar" << "SombreLune" << "kromisback"<< "Wedge"<< "Squirrel";

    m_widgetList.append(new QLabel(ui->m_scrollArea));
    m_widgetList.append(new QLabel(ui->m_scrollArea));
    m_widgetList.append(new QLabel(ui->m_scrollArea));
    m_widgetList.append(new QLabel(ui->m_scrollArea));
    m_widgetList.append(new QLabel(ui->m_scrollArea));
    m_widgetList.append(new QLabel(ui->m_scrollArea));
    m_widgetList.append(new QLabel(ui->m_scrollArea));
    m_widgetList.append(new QLabel(ui->m_scrollArea));
    m_widgetList.append(new QLabel(ui->m_scrollArea));

    //QWidget* wid = new QWidget();
    delete ui->m_scrollArea->layout();
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    ui->m_scrollArea->setLayout(layout);
    int i = 0;
    foreach(QLabel* current,m_widgetList)
    {
        QAction* act = new QAction(QStringLiteral("Label %1").arg(i),this);
        m_actionList.append(act);
        ui->m_hideMenu->addAction(act);
        act->setData(i);
        act->setCheckable(true);
        act->setChecked(current->isVisible());
        connect(act,SIGNAL(triggered(bool)),this,SLOT(showLabel(bool)));
        ++i;
    }
    setImageInLabel();
    foreach(QLabel* current,m_widgetList)
    {
        if(NULL!=current)
        {
            current->setScaledContents(true);
            current->setMaximumHeight(200);
            current->setAlignment(Qt::AlignCenter);
            layout->addWidget(current);
            current->setVisible(true);
        }
    }
   // ui->scrollArea->setWidget(wid);

}
void MainWindow::recordedStart()
{
    qDebug() << "recordedStart()";
    m_timeOfSilence.start();
}

MainWindow::~MainWindow()
{
    for(auto keyItem : m_cumulTimeByUser.keys())
    {
        qDebug() << keyItem <<":"<<m_cumulTimeByUser.value(keyItem) ;
    }
    delete ui;
}
void  MainWindow::displayCorrectImage(QString user)
{
    bool found = false;
    QMap<QString,QString>* map = NULL;
        QList<QString> keys;
    if(ui->actionCops->isChecked())
    {
        map = &m_copsMap;
        keys = m_keyCopOrder;

    }
    else if(ui->actionYoung->isChecked())
    {
        map = &m_youngMap;
        keys = m_keyYoungOrder;

    }
    else if(ui->actionCats->isChecked())
    {
        map = &m_catsMap;
        keys = m_keyCatsOrder;
    }
    else if(ui->m_oneshotAct->isChecked())
    {
        map = &m_l5rOneshotMap;
        keys = m_keyL5rOneshotOrder;
    }
    else if(ui->m_13legion->isChecked())
    {
        map = &m_map13Legion;
        keys = m_key13LegionOrder;
    }
    else if(ui->m_warhammerAct->isChecked())
    {
        map = &m_warHammerMap;
        keys = m_warHammerOrder;
    }
    else if(ui->m_lgIrlAct->isChecked())
    {
        map = &m_lgIrlLegion;
        keys = m_keyLgIrlOrder;
    }
    else if(ui->m_secondeCite->isChecked())
    {
        map = &m_secondeCityS2Map;
        keys = m_secondeCityS2Order;
    }
    else
    {
        map = &m_map;
        keys = m_keyL5rOrder;
    }

    int index = keys.indexOf(user);
    if(index>-1)
    {
        if(m_timeTotalByUser.contains(user))
        {
            QTime* time = m_timeTotalByUser.value(user);

            time->start();
            if(m_numberOfActiveTime==0)
            {

                m_endStr = m_timeOfSilence.elapsed();
                if(m_endStr != 0)
                {
                   // m_fileStream << m_debutStr <<";" << m_endStr << "\n";
                   // m_fileStream.flush();
                }
            }
            ++m_numberOfActiveTime;

            QLabel* current = m_widgetList[index];
            QString img = map->value(user);
            if(NULL!=current)
            {
                current->setPixmap(QPixmap(img));
                found = true;
            }
        }
    }

    if(!found)
    {
        qDebug() << "not found "<< user;
    }
}
void MainWindow::hideImage(QString user)
{
    QMap<QString,QString>* map = NULL;
    QList<QString> keys;

    if(ui->actionCops->isChecked())
    {
        map = &m_copsMap;
        keys = m_keyCopOrder;

    }
    else if(ui->actionYoung->isChecked())
    {
        map = &m_youngMap;
        keys = m_keyYoungOrder;

    }
    else if(ui->actionCats->isChecked())
    {
        map = &m_catsMap;
        keys = m_keyCatsOrder;
    }
    else if(ui->m_oneshotAct->isChecked())
    {
        map = &m_l5rOneshotMap;
        keys = m_keyL5rOneshotOrder;
    }
    else if(ui->m_13legion->isChecked())
    {
        map = &m_map13Legion;
        keys = m_key13LegionOrder;
    }
    else if(ui->m_warhammerAct->isChecked())
    {
        map = &m_warHammerMap;
        keys = m_warHammerOrder;
    }
    else if(ui->m_lgIrlAct->isChecked())
    {
        map = &m_lgIrlLegion;
        keys = m_keyLgIrlOrder;
    }
    else if(ui->m_secondeCite->isChecked())
    {
        map = &m_secondeCityS2Map;
        keys = m_secondeCityS2Order;
    }
    else
    {
        map = &m_map;
        keys = m_keyL5rOrder;
    }
    if(m_timeTotalByUser.contains(user))
    {
        quint64 mili = m_timeTotalByUser.value(user)->elapsed();
        --m_numberOfActiveTime;
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
    if(m_numberOfActiveTime==0)
    {
        m_debutStr = m_timeOfSilence.elapsed();
    }

    int index = keys.indexOf(user);
    if(index>-1)
    {
        QLabel* current = m_widgetList[index];
        QString img = map->value(user);
        if(NULL!=current)
        {
            img.insert(img.lastIndexOf('.'),"-gray");
            current->setPixmap(QPixmap(img));
        }
    }

}
void MainWindow::setImageInLabel()
{

    bool hasChanged=false;
    QObject* wid = qobject_cast<QObject*>(sender());
    if(wid!=NULL)
    {
        hasChanged=true;
    }
    QMap<QString,QString>* map = NULL;
    QList<QString> keys;
    if(ui->actionCops->isChecked())
    {
        map = &m_copsMap;
        keys = m_keyCopOrder;

        setWindowTitle("Cops");
    }
    else if(ui->actionYoung->isChecked())
    {
        map = &m_youngMap;
        keys = m_keyYoungOrder;
        setWindowTitle("Les jeunes L5R");
    }
    else if(ui->actionCats->isChecked())
    {
        map = &m_catsMap;
        keys = m_keyCatsOrder;
        setWindowTitle("Découvertes JDR en Ligne: Cats La mascarade!");

    }
    else if(ui->m_13legion->isChecked())
    {
        map = &m_map13Legion;
        keys = m_key13LegionOrder;
        setWindowTitle("L5R - La 13ème Légion");
    }
    else if(ui->m_oneshotAct->isChecked())
    {
        map = &m_l5rOneshotMap;
        keys = m_keyL5rOneshotOrder;
        setWindowTitle("Oneshot L5R");

    }
    else if(ui->m_warhammerAct->isChecked())
    {
        map = &m_warHammerMap;
        keys = m_warHammerOrder;
        setWindowTitle("Warhammer v2 - Campagne Impériale");

    }
    else if(ui->m_lgIrlAct->isChecked())
    {
        map = &m_lgIrlLegion;
        keys = m_keyLgIrlOrder;
        setWindowTitle("Loup Garou Les déchus - Oneshot découverte");
    }
    else if(ui->m_secondeCite->isChecked())
    {
        map = &m_secondeCityS2Map;
        keys = m_secondeCityS2Order;
        setWindowTitle("L5R - Seconde Cité - Saison 2");
    }
    else
    {
        map = &m_map;
        keys = m_keyL5rOrder;

        setWindowTitle("Le livre des 5 anneaux");
    }

    foreach(QLabel* current,m_widgetList)
    {
        int i = m_widgetList.indexOf(current);
        QAction* act = m_actionList.at(i);
        if(i>-1 && i<keys.size())
        {

            QString img = map->value(keys.at(i));
            m_timeTotalByUser.insert(keys.at(i),new QTime());
            if(NULL!=current)
            {
                current->setText("user");
                setMaximumSizeOnLabel(img,current);
                img.insert(img.lastIndexOf('.'),"-gray");
                current->setPixmap(QPixmap(img));
                if(hasChanged)
                {
                    act->setChecked(hasChanged);
                }
                if(act->isChecked())
                {
                    current->setVisible(true);
                }
            }
        }
        else
        {
            current->setVisible(false);
            act->setChecked(false);
        }
    }
}
void MainWindow::resizeEvent(QResizeEvent * ev)
{
    QMainWindow::resizeEvent(ev);
    setImageInLabel();
}

void MainWindow::setMaximumSizeOnLabel(QString img, QLabel* lbl)
{
    QPixmap pix(img);

    QRect rectImg = pix.rect();
    qreal ratioImg = (qreal)rectImg.width()/rectImg.height();

    qreal normal, adjusted;
    QRect target2 = ui->centralWidget->geometry();//ui->scrollAreaWidgetContents->geometry();
    //qDebug() << target2;
    qreal ratioZone = (qreal)target2.width()/target2.height();

    if(ratioZone>=1)
    {
        adjusted = target2.height()*ratioImg;
        normal = target2.height();
        lbl->setMaximumSize(adjusted,normal-2);
    }
    else
    {
        adjusted = target2.width()/ratioImg;
        normal = target2.width();
        lbl->setMaximumSize(normal,adjusted-2);
    }

}
void MainWindow::setFrameLess()
{
    //setWindowFlags(Qt::FramelessWindowHint);
    ui->menuBar->setVisible(false);
}

void MainWindow::showLabel(bool b)
{
    QAction* action = qobject_cast<QAction*>(sender());
    int i = action->data().toInt();

    if(m_widgetList.size()>i)
    {
        QLabel* label = m_widgetList[i];
        label->setVisible(action->isChecked());
    }
}

