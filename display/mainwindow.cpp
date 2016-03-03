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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint );


    //m_youngMap.insert("Frah",":/resources/Asako.jpg");
    //m_map.insert("Frah",":/resources/Tsuruchi_Nayu.jpg");
    //m_widgetMap.insert("Frah",ui->m_labelTsuruchi);

    connect(ui->m_framelessAct,SIGNAL(triggered()),this,SLOT(setFrameLess()));
    connect(ui->actionCops,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));
    connect(ui->actionYoung,SIGNAL(triggered(bool)),this,SLOT(setImageInLabel()));

    m_map.insert("Akodo Eiichi",":/resources/Mirumoto Tomoe.png");
    //m_map.insert("Akodo Eiichi",":/resources/Akodo_Eiichi.png");
    m_map.insert("Zhia",":/resources/Shinjo_Zhia.jpg");
    m_map.insert("Chewba",":/resources/Bayushi_Takayoshi.png");
    m_map.insert("Obi",":/resources/mj.jpg");

    m_youngMap.insert("Akodo Eiichi",":/resources/kakita.jpg");
    m_youngMap.insert("Zhia",":/resources/Isawa.jpg");
    m_youngMap.insert("Chewba",":/resources/kitsuki.jpg");
    m_youngMap.insert("Obi",":/resources/mj.jpg");

    m_copsMap.insert("Cyb",":/resources/Cops/Rick_Darcy.png");
    m_copsMap.insert("Tlön Uqbar",":/resources/Cops/Guillermo_Gonzalvez.png");
    m_copsMap.insert("Squirrel",":/resources/Cops/Daniel_Mark.png");
    m_copsMap.insert("kromisback",":/resources/Cops/mj.png");
    m_copsMap.insert("Obi",":/resources/Cops/Lynn_Gray-Rike.png");
    m_copsMap.insert("Wedge",":/resources/Cops/Denis_Aquillian.png");



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

MainWindow::~MainWindow()
{
    delete ui;
}
void  MainWindow::displayCorrectImage(QString user)
{
    bool found = false;
    QMap<QString,QString>* map = NULL;
    if(ui->actionCops->isChecked())
    {
        map = &m_copsMap;
    }
    else if(ui->actionYoung->isChecked())
    {
        map = &m_youngMap;
    }
    else
    {
        map = &m_map;
    }
    int index = map->keys().indexOf(user);
    if(index>-1)
    {
        QLabel* current = m_widgetList[index];
        QString img = map->value(user);
        if(NULL!=current)
        {
            current->setPixmap(QPixmap(img));
            found = true;
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
    if(ui->actionCops->isChecked())
    {
        map = &m_copsMap;
    }
    else if(ui->actionYoung->isChecked())
    {
        map = &m_youngMap;
    }
    else
    {
        map = &m_map;
    }

    int index = map->keys().indexOf(user);
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
    QMap<QString,QString>* map = NULL;
    if(ui->actionCops->isChecked())
    {
        map = &m_copsMap;
        setWindowTitle("Cops");
    }
    else if(ui->actionYoung->isChecked())
    {
        map = &m_youngMap;
        setWindowTitle("Les jeunes L5R");
    }
    else
    {
        map = &m_map;
        setWindowTitle("Le livre des 5 anneaux");
    }

    foreach(QLabel* current,m_widgetList)
    {
        int i = m_widgetList.indexOf(current);
        if(i>-1 && i<map->values().size())
        {
            QString img = map->values().at(i);
            if(NULL!=current)
            {
                //qDebug() << "setImg in label"<< img << current  ;
                current->setText("user");
                setMaximumSizeOnLabel(img,current);
                img.insert(img.lastIndexOf('.'),"-gray");
                current->setPixmap(QPixmap(img));
                current->setVisible(true);
            }
        }
        else
        {
            current->setVisible(false);
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

