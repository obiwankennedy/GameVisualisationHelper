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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QLabel>
#include <QFile>
#include <QTime>
#include <QTextStream>
#include <QQmlApplicationEngine>

namespace Ui {
class MainWindow;
}

class PresentProxyModel;
class CharacterAvatarModel;
class SelectPresentProxyModel;
/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void displayCorrectImage(QString user);
    void hideImage(QString user);
	void setImageInLabel();

protected:
	void resizeEvent(QResizeEvent *);
signals:
    void changeCurrentAvatar(QString);

private:
    Ui::MainWindow *ui;

    PresentProxyModel* m_proxyModel;
    SelectPresentProxyModel* m_selectModel;
    CharacterAvatarModel* m_model;
    QQmlApplicationEngine* m_engine;

    QMap<QString,QTime*> m_timeTotalByUser;
    QMap<QString,qreal> m_cumulTimeByUser;
    QFile* m_file;
    QTextStream m_fileStream;
};

#endif // MAINWINDOW_H
