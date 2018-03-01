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

namespace Ui {
class MainWindow;
}

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
    void recordedStart();

private slots:
	void setMaximumSizeOnLabel(QString img, QLabel* lbl);
    void setFrameLess();
    void showLabel(bool);

protected:
	void resizeEvent(QResizeEvent *);
signals:
    void changeCurrentAvatar(QString);

private:
    Ui::MainWindow *ui;

    QMap<QString,QString> m_map;
    QMap<QString,QString> m_map13Legion;
    QMap<QString,QString> m_lgIrlLegion;
    QMap<QString,QString> m_youngMap;
    QMap<QString,QString> m_catsMap;
    QMap<QString,QString> m_l5rOneshotMap;
    QMap<QString,QString> m_warHammerMap;
    QMap<QString,QString> m_secondeCityS2Map;

    QList<QString> m_keyCopOrder;
    QList<QString> m_key13LegionOrder;
    QList<QString> m_keyYoungOrder;
    QList<QString> m_keyL5rOrder;
    QList<QString> m_keyL5rOneshotOrder;
    QList<QString> m_keyCatsOrder;
    QList<QString> m_keyLgIrlOrder;
    QList<QString> m_warHammerOrder;
    QList<QString> m_secondeCityS2Order;


    QMap<QString,QString> m_copsMap;
    QList<QLabel*>  m_widgetList;
    QList<QAction*>  m_actionList;
    QMap<QString,QTime*> m_timeTotalByUser;
    QMap<QString,qreal> m_cumulTimeByUser;
    int m_numberOfActiveTime;
    QTime m_timeOfSilence;
    quint64 m_debutStr;
    quint64 m_endStr;
    QFile* m_file;
    QTextStream m_fileStream;
};

#endif // MAINWINDOW_H
