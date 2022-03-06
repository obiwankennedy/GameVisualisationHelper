/***************************************************************************
 *	Copyright (C) 2022 by Renaud Guezennec                               *
 *   http://www.rolisteam.org/contact                                      *
 *                                                                         *
 *   This software is free software; you can redistribute it and/or modify *
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
#include "maincontroller.h"
#include "character.h"

#include <QDate>

MainController::MainController(QObject* parent)
    : QObject{parent}
    , m_avatarModel{new CharacterAvatarModel}
    , m_proxyModel{new PresentProxyModel}
    , m_selectModel{new SelectPresentProxyModel}
    , m_diaporamaModel{new DiaporamaModel}
{
    m_avatarModel->addPerson(new Character(QStringLiteral("Obi (Mj)"), QStringLiteral("Obi"),
                                           QStringLiteral("qrc:/resources/L5RRiz/Perso/mj.jpg"),
                                           QStringLiteral("jeudi"), QColor("#9C9C00"), "_mj", true));

    auto today= QDate::currentDate();
    auto w= today.weekNumber();
    if(w % 2 == 1)
    {
        m_table1= true;
        m_avatarModel->addPerson(new Character(QStringLiteral("Yasuki Gosetsu"), QStringLiteral("Caladbolg"),
                                               QStringLiteral("qrc:/resources/L5RRiz/Perso/Gosetsu.png"),
                                               QStringLiteral("jeudi"), QColor("#888800"), "_first"));

        m_avatarModel->addPerson(new Character(QStringLiteral("Kaiu Ryūjirō"), QStringLiteral("Elaryon"),
                                               QStringLiteral("qrc:/resources/L5RRiz/Perso/kaiu_Ryujiro.png"),
                                               QStringLiteral("jeudi"), QColor("#008888"), "_second"));

        m_avatarModel->addPerson(new Character(QStringLiteral("Kuni Aka"), QStringLiteral("Capitaine Red"),
                                               QStringLiteral("qrc:/resources/L5RRiz/Perso/aka.png"),
                                               QStringLiteral("jeudi"), QColor(Qt::darkBlue), "_third"));

        m_avatarModel->addPerson(new Character(QStringLiteral("Yasuki Dazai"), QStringLiteral("Houss"),
                                               QStringLiteral("qrc:/resources/L5RRiz/Perso/yasuki_dazai.png"),
                                               QStringLiteral("jeudi"), QColor(Qt::darkBlue), "_fourth"));
    }
    else
    {
        m_table1= false;
        m_avatarModel->addPerson(new Character(QStringLiteral("Kakita Yoaka"), QStringLiteral("Shaka"),
                                               QStringLiteral("qrc:/resources/L5RRiz/Perso/Kakita_Yoake.png"),
                                               QStringLiteral("jeudi"), QColor("#888800"), "_first"));

        m_avatarModel->addPerson(new Character(QStringLiteral("Komori Kokoe"), QStringLiteral("brind'if"),
                                               QStringLiteral("qrc:/resources/L5RRiz/Perso/Kokoe.jpg"),
                                               QStringLiteral("jeudi"), QColor("#008888"), "_second"));

        m_avatarModel->addPerson(new Character(QStringLiteral("Tsuruchi Suda"), QStringLiteral("Ritton-T"),
                                               QStringLiteral("qrc:/resources/L5RRiz/Perso/tsuruchi_suda.jpg"),
                                               QStringLiteral("jeudi"), QColor(Qt::darkBlue), "_third"));

        m_avatarModel->addPerson(new Character(QStringLiteral("Ichiro Kunika"), QStringLiteral("Kyuha"),
                                               QStringLiteral("qrc:/resources/L5RRiz/Perso/Ichiro_Kunika.png"),
                                               QStringLiteral("jeudi"), QColor(Qt::darkBlue), "_fourth"));
    }
    m_proxyModel->setSourceModel(m_avatarModel.get());
    m_selectModel->setSourceModel(m_avatarModel.get());

    connect(m_avatarModel.get(), &CharacterAvatarModel::totaltimeChanged, this,
            &MainController::maxSpeakingTimeChanged);
}

MainController::~MainController()= default;

CharacterAvatarModel* MainController::avatarModel() const
{
    return m_avatarModel.get();
}

Character* MainController::gameMaster() const
{
    return m_avatarModel->characterAt(0);
}

Character* MainController::characterOne() const
{
    return m_avatarModel->characterAt(1);
}

Character* MainController::characterTwo() const
{
    return m_avatarModel->characterAt(2);
}

Character* MainController::characterThree() const
{
    return m_avatarModel->characterAt(3);
}

Character* MainController::characterFour() const
{
    return m_avatarModel->characterAt(4);
}

bool MainController::table1() const
{
    return m_table1;
}

const QString& MainController::campaign() const
{
    return m_campaign;
}

void MainController::setCampaign(const QString& newCampaign)
{
    if(m_campaign == newCampaign)
        return;
    m_campaign= newCampaign;
    emit campaignChanged();

    m_proxyModel->setCurrentCampaign(m_campaign);
    m_selectModel->setCurrentCampaign(m_campaign);
}

PresentProxyModel* MainController::proxyModel() const
{
    return m_proxyModel.get();
}

SelectPresentProxyModel* MainController::selectModel() const
{
    return m_selectModel.get();
}

DiaporamaModel* MainController::diaporamaModel() const
{
    return m_diaporamaModel.get();
}

qreal MainController::maxSpeakingTime() const
{
    return m_avatarModel->maxSpeakingTime();
}
