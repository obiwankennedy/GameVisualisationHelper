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
    setWindowFlags(Qt::WindowStaysOnTopHint);



    m_map.insert("Akodo Eiichi",":/resources/Akodo_Eiichi.png");
    m_map.insert("Frah",":/resources/Tsuruchi_Nayu.jpg");
    m_map.insert("Shinjo Zhia",":/resources/Shinjo_Zhia.jpg");
    m_map.insert("Chewba",":/resources/Bayushi_Takayoshi.png");
    m_map.insert("obi",":/resources/mj.jpg");

    m_youngMap.insert("Akodo Eiichi",":/resources/kakita.jpg");
    m_youngMap.insert("Shinjo Zhia",":/resources/Isawa.jpg");
    m_youngMap.insert("Chewba",":/resources/kitsuki.jpg");
    m_youngMap.insert("Frah",":/resources/Asako.jpg");
    m_youngMap.insert("obi",":/resources/mj.jpg");

}

MainWindow::~MainWindow()
{
    delete ui;
}
void  MainWindow::displayCorrectImage(QString user)
{
    QMap<QString,QString>* map = NULL;
    if(ui->actionYoung->isChecked())
    {
        map = &m_youngMap;
    }
    else
    {
        map = &m_map;
    }

    foreach(QString name,map->keys())
    {
        if(user.contains(name,Qt::CaseInsensitive))
        {

            ui->label->setText(name);
            ui->label->setPixmap(QPixmap(map->value(name)));

        }
    }
}
void MainWindow::hideImage(QString user)
{
	
}
