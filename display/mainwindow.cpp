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
    ui->m_oneshotAct->setChecked(true);
   /* m_file = new QFile(QString("/home/renaud/Parties/%1_silence_%2.txt").arg(str).arg(QDate::currentDate().toString("yyyy_MM_dd")));
    if(m_file->open(QIODevice::WriteOnly))
    {
        m_fileStream.setDevice(m_file);
    }
    else
    {
        qDebug() << "Impossible to create file at:"<< m_file->fileName() ;
    }*/

    //m_youngMap.insert("Frah",":/resources/Asako.jpg");
    //m_map.insert("Frah",":/resources/Tsuruchi_Nayu.jpg");
    //m_widgetMap.insert("Frah",ui->m_labelTsuruchi);

    connect(ui->m_framelessAct,SIGNAL(triggered()),this,SLOT(setFrameLess()));
    connect(ui->actionCops,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));
    connect(ui->actionCats,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));
    connect(ui->m_oneshotAct,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));


    //m_map.insert("Akodo Eiichi",":/resources/Mirumoto Tomoe.png");
    m_map.insert("Akodo Eiichi",":/resources/Akodo_Eiichi.png");
    m_map.insert("Capitaine Red",":/resources/Shinjo_Zhia.jpg");
    //m_map.insert("Zhia",":/resources/hidaMaki1.jpg");
    //m_map.insert("Zhia",":/resources/Asako_misako.png");
    //m_map.insert("Zhia",":/resources/Saito.jpg");

    m_map.insert("Chewba",":/resources/Bayushi_Takayoshi.png");
    //m_map.insert("Chewba",":/resources/Saito.jpg");
    //m_map.insert("Chewba",":/resources/Asako_misako.png");
    m_map.insert("Obi",":/resources/oneshot/Daidoji_Hiru.jpg");
    m_keyL5rOrder<< "Akodo Eiichi" << "Capitaine Red" << "Chewba" << "Obi"  ;


    ///CATs
    m_catsMap.insert("Leia Tortoise",":/resources/cats/arsene2.jpg");
   // m_catsMap.insert("Gilgamesh",":/resources/cats/Ghandi.jpg");
    m_catsMap.insert("HyiHyil",":/resources/cats/Hercule.jpg");
    m_catsMap.insert("Gilgamesh",":/resources/cats/Sherlock.jpg");
    m_catsMap.insert("Selawyr",":/resources/cats/tatcher.jpg");

    m_catsMap.insert("Obi",":/resources/cats/Matou_Jovial.jpg");

    m_keyCatsOrder << "HyiHyil" << "Leia Tortoise" << "Selawyr" <<  "Gilgamesh" << "Obi";


    ///YOUNG
    m_youngMap.insert("Akodo Eiichi",":/resources/kakita.jpg");
    m_youngMap.insert("Capitaine Red",":/resources/Isawa.jpg");
    m_youngMap.insert("Chewba",":/resources/kitsuki.jpg");
    m_youngMap.insert("Obi",":/resources/oneshot/Daidoji_Hiru.jpg");
    m_keyYoungOrder << "Akodo Eiichi" << "Capitaine Red" << "Chewba" << "Obi"  ;



    ///// ONESHOT L5R
    m_l5rOneshotMap.insert("anaisurprise",":/resources/oneshot/Tsuruchi_Tamoe.jpg");
    m_l5rOneshotMap.insert("Flow0333",":/resources/oneshot/Mirumoto_Kitsawa.jpg");
    m_l5rOneshotMap.insert("Wedge",":/resources/oneshot/Isawa_Kenko.jpg");
    m_l5rOneshotMap.insert("brice",":/resources/oneshot/Hida_Kokujin.jpg");
    m_l5rOneshotMap.insert("pseudo6",":/resources/oneshot/Daidoji_Hiru.jpg");
    m_l5rOneshotMap.insert("Natsu*",":/resources/oneshot/Bayushi_Sahime.jpg");
    m_l5rOneshotMap.insert("Ciennte",":/resources/oneshot/Akodo_Neru.jpg");
    m_l5rOneshotMap.insert("Obi",":/resources/mj.jpg");

    m_keyL5rOneshotOrder << "anaisurprise"<< "Flow0333"<< "Wedge"<< "brice" << "pseudo6"<< "Natsu*"<< "Ciennte"<< "Obi";

    //COPS
  //  m_copsMap.insert("Cyb",":/resources/Cops/Rick_Darcy.png");
    m_copsMap.insert("TlonUqbar",":/resources/Cops/Guillermo_Gonzalvez.png");
    m_copsMap.insert("Chewba",":/resources/Cops/max_ohara_bis.jpg");
    //m_copsMap.insert("Squirrel",":/resources/Cops/Daniel_Mark.png");
    m_copsMap.insert("Obi",":/resources/Cops/Lynn_Gray-Rike.png");
    m_copsMap.insert("Wedge",":/resources/Cops/Denis_Aquillian.png");
   // m_copsMap.insert("Cocoon",":/resources/Cops/Christopher_Atkins.jpg");
    m_copsMap.insert("kromisback",":/resources/Cops/mj.png");
//<< "Cocoon"

    m_keyCopOrder  << "Obi" << "TlonUqbar" << "Chewba"<< "Wedge"<< "kromisback";









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
    else if(ui->m_oneshotAct->isChecked())
    {
        map = &m_l5rOneshotMap;
        keys = m_keyL5rOneshotOrder;
        setWindowTitle("Oneshot L5R");

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

