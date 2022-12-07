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
#ifndef MAIN
#define MAIN
#include "guiadaptor.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QImageReader>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>

int main(int argc, char* argv[])
{
    QtWebEngineQuick::initialize();
    QApplication a(argc, argv);
    a.setApplicationName("L5R display");
    a.setOrganizationName("rolisteam");
    a.setOrganizationDomain("rolisteam.org");
    MainWindow* w= new MainWindow();
    new GuiAdaptor(w);
    w->show();

    QImageReader::setAllocationLimit(0);


    QDBusConnection connection= QDBusConnection::sessionBus();
    bool rel= connection.registerService("org.rolisteam.display");
    rel= connection.registerObject("/", w);

    return a.exec();
}

#endif
