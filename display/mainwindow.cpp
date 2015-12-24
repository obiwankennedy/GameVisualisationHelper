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



    connect(ui->m_framelessAct,SIGNAL(triggered()),this,SLOT(setFrameLess()));

    m_map.insert("Akodo Eiichi",":/resources/Akodo_Eiichi.png");
    //m_map.insert("Frah",":/resources/Tsuruchi_Nayu.jpg");
    m_map.insert("Zhia",":/resources/Shinjo_Zhia.jpg");
    m_map.insert("Chewba",":/resources/Bayushi_Takayoshi.png");
    m_map.insert("obi",":/resources/mj.jpg");

    m_youngMap.insert("Akodo Eiichi",":/resources/kakita.jpg");
    m_youngMap.insert("Zhia",":/resources/Isawa.jpg");
    m_youngMap.insert("Chewba",":/resources/kitsuki.jpg");
    //m_youngMap.insert("Frah",":/resources/Asako.jpg");
    m_youngMap.insert("obi",":/resources/mj.jpg");


	m_widgetMap.insert("Akodo Eiichi",ui->m_labelAkodo);
    m_widgetMap.insert("Zhia",ui->m_labelShinjo);
	m_widgetMap.insert("Chewba",ui->m_labelBauyshi);
    //m_widgetMap.insert("Frah",ui->m_labelTsuruchi);
    ui->m_labelTsuruchi->setVisible(false);
	m_widgetMap.insert("obi",ui->m_gmlabel);

	setImageInLabel();

	foreach(QLabel* current,m_widgetMap.values())
	{
		if(NULL!=current)
		{
			current->setVisible(true);
			hideImage(m_widgetMap.key(current));
		}
	}
}

MainWindow::~MainWindow()
{
    delete ui;
}
void  MainWindow::displayCorrectImage(QString user)
{
	bool found = false;
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
		if(name.contains(user,Qt::CaseInsensitive))
		{
			QLabel* current     = m_widgetMap[name];
			QString img = map->value(name);
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
		if(name.contains(user,Qt::CaseInsensitive))
		{
			QLabel* current     = m_widgetMap[name];
			QString img = map->value(name);
			if(NULL!=current)
			{
				img.insert(img.lastIndexOf('.'),"-gray");
				current->setPixmap(QPixmap(img));
			}

		}
	}
}
void MainWindow::setImageInLabel()
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
	foreach(QString name,m_widgetMap.keys())
	{
		QString img = map->value(name);
		QLabel* current     = m_widgetMap[name];
		if(NULL!=current)
		{
			setMaximumSizeOnLabel(img,current);
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
		lbl->setMaximumSize(adjusted,normal);
	}
	else
	{
		adjusted = target2.width()/ratioImg;
		normal = target2.width();
		lbl->setMaximumSize(normal,adjusted);
	}

}
void MainWindow::setFrameLess()
{
    //setWindowFlags(Qt::FramelessWindowHint);
    ui->menuBar->setVisible(false);
}
