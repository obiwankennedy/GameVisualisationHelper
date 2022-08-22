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

#include <QCloseEvent>
#include <QElapsedTimer>
#include <QFile>
#include <QLabel>
#include <QMainWindow>
#include <QMap>
#include <QQmlApplicationEngine>
#include <QSortFilterProxyModel>
#include <QTextStream>
#include <memory>

namespace Ui
{
class MainWindow;
}

class PresentProxyModel;
class CharacterAvatarModel;
class SelectPresentProxyModel;
class MainController;
class CharacterController;
/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent= nullptr);
    ~MainWindow();

    bool maybeSave();
    void refreshQMLEngine();
public slots:
    void displayCorrectImage(QString user);
    void hideImage(QString user);
    void loadFile();

    void saveFile(bool saveAs= false);

protected:
    void resizeEvent(QResizeEvent*);
    void closeEvent(QCloseEvent* event);

signals:
    void changeCurrentAvatar(QString);

private slots:
    void on_actionRefresh_triggered();

    void on_actionErase_Time_triggered();
    void generateSheetForAll();

private:
    Ui::MainWindow* ui;
    std::unique_ptr<MainController> m_ctrl;
    std::unique_ptr<CharacterController> m_characterCtrl;

    SelectPresentProxyModel* m_selectModel;
    std::unique_ptr<QQmlApplicationEngine> m_engine;

    QMap<QString, QElapsedTimer*> m_timeTotalByUser;
    QMap<QString, qreal> m_cumulTimeByUser;
    std::unique_ptr<QSortFilterProxyModel> m_haikuFiltered;
    // QFile* m_file;
    QTextStream m_fileStream;
    QString m_filename;

    // QACTION
    QAction* m_addHaiku{nullptr};

    QAction* m_generateAgeForAll{nullptr};
    QAction* m_generateSheetForAll{nullptr};

    QTimer* m_updateMarkDown;
};

#endif // MAINWINDOW_H
