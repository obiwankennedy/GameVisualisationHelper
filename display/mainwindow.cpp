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

#include <QDate>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QQmlContext>
#include <QRandomGenerator>
#include <QSaveFile>
#include <QTimer>

#include "characteravatarmodel.h"
#include "controller/charactercontroller.h"
#include "maincontroller.h"
#include "player.h"
#include "presentproxymodel.h"
#include "utils/iohelper.h"
#include "widgets/l5rcharactersheetdialog.h"

#include "checkboxdelegate.h"
#include "clandelegate.h"

constexpr int WaitingTime{1000 * 30};

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_ctrl(new MainController)
    , m_characterCtrl(new CharacterController)
    , m_haikuFiltered(new QSortFilterProxyModel)
{
    ui->setupUi(this);
    // setWindowFlags(Qt::WindowStaysOnTopHint);

    QStringList camp;
    camp << "jeudi";
    ui->comboBox->addItems(camp);

    m_filename= m_ctrl->table1() ? "/home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/15_riz/table1.cdb" :
                                   "/home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/15_riz/table2.cdb";

    connect(ui->actionSave_As, &QAction::triggered, this, [this]() { saveFile(true); });
    connect(ui->actionSave, &QAction::triggered, this, [this]() { saveFile(false); });
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::loadFile);

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, [this](QString str) { m_ctrl->setCampaign(str); });

    ui->m_presentList->setModel(m_ctrl->selectModel());

    ui->m_characterView->setModel(m_ctrl->proxyModel());
    auto currentCampaign= "jeudi";

    auto sorted= m_ctrl->sortedModel();
    sorted->setSourceModel(m_characterCtrl->filteredModel());

    m_ctrl->setCampaign(currentCampaign);
    ui->comboBox->setCurrentText(currentCampaign);

    ui->m_tableview->setModel(m_characterCtrl->filteredModel());
    ui->m_tableview->setItemDelegateForColumn(5, new ClanDelegate());
    ui->m_tableview->setItemDelegateForColumn(7, new CheckBoxDelegate());
    ui->m_tableview->setContextMenuPolicy(Qt::ActionsContextMenu);

    m_generateAgeForAll= new QAction(tr("Set Age for All"), ui->m_tableview);
    m_generateSheetForAll= new QAction(tr("Sheet for All"), ui->m_tableview);
    connect(m_generateAgeForAll, &QAction::triggered, this, [this]() {
        auto rows= m_characterCtrl->filteredModel()->rowCount();

        for(auto i= 0; i < rows; ++i)
        {
            m_characterCtrl->filteredModel()->setData(m_characterCtrl->filteredModel()->index(i, 4),
                                                      QRandomGenerator::global()->bounded(20, 60));
        }
    });

    connect(m_generateAgeForAll, &QAction::triggered, this, &MainWindow::generateSheetForAll);

    ui->m_tableview->addAction(m_generateAgeForAll);
    ui->m_tableview->addAction(m_generateSheetForAll);

    auto header= ui->m_tableview->horizontalHeader();
    header->setSectionResizeMode(2, QHeaderView::Stretch);
    header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(4, QHeaderView::ResizeToContents);

    // Preview
    auto label= new QLabel();
    label->setLineWidth(0);
    label->setFrameStyle(QFrame::NoFrame);
    ui->m_scrollAreaVisual->setWidget(label);
    ui->m_scrollAreaVisual->setAlignment(Qt::AlignCenter);
    ui->m_scrollAreaVisual->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->m_scrollAreaVisual->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    label->setScaledContents(true);
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    m_ctrl->previewCtrl()->setLabel(label);
    label->installEventFilter(m_ctrl->previewCtrl());

    connect(m_ctrl->previewCtrl(), &PreviewController::imageChanged, this,
            [this, label]() { label->setPixmap(QPixmap::fromImage(m_ctrl->previewCtrl()->image())); });

    connect(ui->m_visualModeCb, &QComboBox::currentIndexChanged, m_ctrl->previewCtrl(),
            &PreviewController::setCurrentMode);

    // Table view
    auto vHeader= ui->m_tableview->verticalHeader();
    vHeader->setDefaultSectionSize(60);

    connect(ui->m_tableview, &QTableView::doubleClicked, this, [this](const QModelIndex& index) {
        if(!index.isValid())
            return;

        if(index.column() != 10)
            return;

        auto model= ui->m_tableview->model();

        auto sheet= model->data(index, CharacterModel::SheetPropertiesRole).value<QHash<QString, QString>>();
        qDebug() << "sheet " << sheet;

        L5RCharacterSheetDialog dia(sheet);

        dia.exec();

        model->setData(index, QVariant::fromValue(dia.sheetProperties()), CharacterModel::SheetPropertiesRole);
    });

    auto filter= m_characterCtrl->filteredModel();

    connect(ui->m_patternLine, &QLineEdit::editingFinished, filter,
            [filter, this]() { filter->setPattern(ui->m_patternLine->text()); });
    connect(ui->m_genderCb, &QComboBox::currentTextChanged, filter, [filter, this]() {
        auto idx= ui->m_genderCb->currentIndex();
        filter->setGender(idx == 0 ? core::Gender::All : idx == 1 ? core::Gender::Masculin : core::Gender::Feminin);
    });
    connect(ui->m_tableCb, &QComboBox::currentTextChanged, filter, [filter, this]() {
        auto idx= ui->m_tableCb->currentIndex();
        filter->setTable(idx == 0 ? core::Table::All : idx == 1 ? core::Table::Table1 : core::Table::Table2);
    });

    connect(ui->m_clanCb, &QComboBox::currentTextChanged, filter, [filter, this]() {
        auto idx= ui->m_clanCb->currentIndex();
        filter->setClan(idx == 0 ? QString() : ui->m_clanCb->currentText());
    });
    connect(ui->m_factionCb, &QComboBox::currentTextChanged, filter, [filter, this]() {
        auto idx= ui->m_factionCb->currentIndex();
        filter->setFaction(idx == 0 ? QString() : ui->m_factionCb->currentText());
    });
    connect(ui->m_ownerCb, &QComboBox::currentTextChanged, filter, [filter, this]() {
        auto idx= ui->m_ownerCb->currentIndex();
        filter->setOwner(idx == 0 ? QString() : ui->m_ownerCb->currentText());
    });

    connect(ui->m_ignoredLine, &QLineEdit::editingFinished, filter,
            [filter, this]() { filter->setIgnoredPattern(ui->m_ignoredLine->text()); });

    connect(ui->m_statusCb, &QComboBox::currentIndexChanged, filter, [filter, this]() {
        switch(ui->m_statusCb->currentIndex())
        {
        case 0:
            filter->setStatus(core::Status::All);
            break;
        case 1:
            filter->setStatus(core::Status::Samurai);
            break;
        case 2:
            filter->setStatus(core::Status::NonSamurai);
            break;
        }
    });

    connect(ui->m_hideDead, &QCheckBox::toggled, this,
            [filter, this]() { filter->setHideDead(ui->m_hideDead->isChecked()); });

    connect(ui->m_hideNoAvatar, &QCheckBox::toggled, this,
            [filter, this]() { filter->setHideNoAvatar(ui->m_hideNoAvatar->isChecked()); });

    connect(ui->m_resetBtn, &QPushButton::clicked, this, [filter, this]() {
        ui->m_patternLine->setText(QString());
        ui->m_genderCb->setCurrentIndex(0);
        ui->m_tableCb->setCurrentIndex(0);
        ui->m_clanCb->setCurrentIndex(0);
        ui->m_factionCb->setCurrentIndex(0);
        ui->m_ownerCb->setCurrentIndex(0);

        filter->setClan(QString());
        filter->setPattern(QString());
        filter->setFaction(QString());
        filter->setOwner(QString());
        filter->setTable(core::Table::All);
        filter->setGender(core::Gender::All);
        // filter->setClan(QString());
    });

    ui->m_clanCb->addItems(m_characterCtrl->clanModel());
    ui->m_factionCb->addItems(m_characterCtrl->factionModel());
    ui->m_ownerCb->addItems(m_characterCtrl->ownerModel());

    m_addHaiku= new QAction{tr("Add Haiku"), this};

    connect(m_addHaiku, &QAction::triggered, this, [this]() {
        auto text= QInputDialog::getMultiLineText(this, tr("Your haiku"), tr("Your haiku"));
        m_ctrl->haikus()->addHaiku(text);
    });

    m_haikuFiltered->setSourceModel(m_ctrl->haikus());
    m_haikuFiltered->setDynamicSortFilter(true);
    m_haikuFiltered->setFilterCaseSensitivity(Qt::CaseInsensitive);
    connect(ui->m_haikuTextEdit, &QLineEdit::textChanged, m_haikuFiltered.get(),
            &QSortFilterProxyModel::setFilterFixedString);

    connect(ui->m_haikuList, &QListView::customContextMenuRequested, this, [this](const QPoint& point) {
        QMenu menu;

        menu.addAction(m_addHaiku);
        menu.exec(point);
    });

    ui->m_haikuList->setModel(m_haikuFiltered.get());

    loadFile();
    refreshQMLEngine();

    QObject* root= m_engine->rootObjects().first();
    if(nullptr != root)
    {
        auto window= qobject_cast<QQuickWindow*>(root);
        connect(window, &QQuickWindow::frameSwapped, this,
                [this, window]() { m_ctrl->previewCtrl()->setImage(window->grabWindow()); });

        connect(m_ctrl->previewCtrl(), &PreviewController::sendEvent, this,
                [window](QMouseEvent* event) { QCoreApplication::sendEvent(window, event); });
    }

    QFile file("/home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/15_riz/01_Notes.md");
    if(file.open(QIODevice::ReadOnly))
    {
        auto data= file.readAll();
        ui->m_editor->setPlainText(data);
        ui->m_viewer->setMarkdown(data);
    }

    m_updateMarkDown= new QTimer(this);

    connect(m_updateMarkDown, &QTimer::timeout, this, [this] {
        ui->m_viewer->setMarkdown(ui->m_editor->toPlainText());
        m_updateMarkDown->stop();
    });

    connect(ui->m_editor, &QPlainTextEdit::textChanged, ui->m_viewer,
            [this]() { m_updateMarkDown->start(WaitingTime); });
}

MainWindow::~MainWindow() {}

void MainWindow::refreshQMLEngine()
{
    m_engine.reset(new QQmlApplicationEngine());

    qmlRegisterSingletonType<MainController>("Controller", 1, 0, "MainController",
                                             [this](QQmlEngine* engine, QJSEngine*) {
                                                 engine->setObjectOwnership(m_ctrl.get(), QQmlEngine::CppOwnership);
                                                 return m_ctrl.get();
                                             });
    qmlRegisterUncreatableType<CalendarItemModel>("MainController", 1, 0, "CalendarItemModel",
                                                  "Can't be instantiate in qml");

    m_engine->load(QUrl("qrc:/qml/main.qml"));
    setAttribute(Qt::WA_DeleteOnClose, true);

    ui->m_calendrier->setSource(QUrl("qrc:/qml/Calendrier.qml"));
}

void MainWindow::displayCorrectImage(QString user)
{
    if(user.compare("obi1", Qt::CaseInsensitive) == 0)
        return;

    m_ctrl->avatarModel()->speakingStatusChanged(user, true);
    if(!m_timeTotalByUser.contains(user))
    {
        m_timeTotalByUser.insert(user, new QElapsedTimer());
    }

    QElapsedTimer* time= m_timeTotalByUser.value(user);
    time->start();
}
void MainWindow::hideImage(QString user)
{
    if(user.compare("obi1", Qt::CaseInsensitive) == 0)
        return;

    m_ctrl->avatarModel()->speakingStatusChanged(user, false);
    if(m_timeTotalByUser.contains(user))
    {
        quint64 mili= m_timeTotalByUser.value(user)->elapsed();

        qreal time= (qreal)mili / 1000.0;
        if(m_cumulTimeByUser.contains(user))
        {
            m_cumulTimeByUser[user]+= time;
        }
        else
        {
            m_cumulTimeByUser.insert(user, time);
        }

        if(m_ctrl->avatarModel()->maxSpeakingTime() < m_cumulTimeByUser[user])
        {
            m_ctrl->avatarModel()->setMaxSpeakingTime(m_cumulTimeByUser[user]);
        }
        m_ctrl->avatarModel()->setSpeakingTimeForUser(user, ui->comboBox->currentText(), m_cumulTimeByUser[user]);
    }
}

void MainWindow::loadFile()
{
    if(m_filename.isEmpty())
    {
        QString filename
            = QFileDialog::getOpenFileName(this, tr("Load file"), QDir::homePath(), "Character Base (*.cdb *.json)");
        if(filename.isEmpty())
            return;

        m_filename= filename;
    }

    QFile file(m_filename);
    file.open(QIODevice::ReadOnly);
    QJsonDocument doc= QJsonDocument::fromJson(file.readAll());
    auto array= doc.array();
    m_ctrl->avatarModel()->readData(array);
    IOHelper::fetchCalendarModel(m_ctrl->calendarModel());
}

void MainWindow::saveFile(bool saveAs)
{
    if(saveAs || m_filename.isEmpty())
    {
        QString filename
            = QFileDialog::getSaveFileName(this, tr("Save file"), QDir::homePath(), "Character Base (*.cdb *.json)");
        if(filename.isEmpty())
            return;
        m_filename= filename;
    }

    QJsonDocument doc;
    QJsonArray array;
    m_ctrl->avatarModel()->writeData(array);

    doc.setArray(array);
    QFile file(m_filename);
    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson());

    QSaveFile savefile("/home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/15_riz/01_Notes.md");
    if(savefile.open(QIODevice::WriteOnly))
    {
        savefile.write(ui->m_editor->toPlainText().toUtf8());
        savefile.commit();
    }

    IOHelper::writeCalendarModel(m_ctrl->calendarModel());
}
void MainWindow::resizeEvent(QResizeEvent* ev)
{
    QMainWindow::resizeEvent(ev);
}
bool MainWindow::maybeSave()
{
    return true;
}
void MainWindow::closeEvent(QCloseEvent* event)
{
    if(maybeSave())
    {
        qDebug() << "delete mainwindow" << m_cumulTimeByUser.size();
        for(const auto& keyItem : m_cumulTimeByUser.keys())
        {
            qDebug() << keyItem << ":" << m_cumulTimeByUser.value(keyItem);
        }
        saveFile(false);
        m_characterCtrl->saveModel();
        m_ctrl->haikus()->writeModel();
        event->accept();
    }
    else
    {
        event->ignore();
    }
    qApp->quit();
}

void MainWindow::on_actionRefresh_triggered()
{
    refreshQMLEngine();
}

void MainWindow::on_actionErase_Time_triggered()
{
    for(auto it= m_cumulTimeByUser.begin(); it != m_cumulTimeByUser.end(); ++it)
    {
        it.value()= 0;
    }
}

void MainWindow::generateSheetForAll()
{
    /*auto rows= m_characterCtrl->filteredModel()->rowCount();

    for(auto i= 0; i < rows; ++i)
    {
        m_characterCtrl->filteredModel()->setData(m_characterCtrl->filteredModel()->index(i, 4),
                                                  QRandomGenerator::global()->bounded(20, 60));
    }*/
}
