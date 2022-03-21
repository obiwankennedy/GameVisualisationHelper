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
#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

#include "characteravatarmodel.h"
#include "controller/previewcontroller.h"
#include "diaporamamodel.h"
#include "model/sortedmodel.h"
#include "player.h"
#include "presentproxymodel.h"

class MainController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CharacterAvatarModel* avatarModel READ avatarModel CONSTANT)
    Q_PROPERTY(PresentProxyModel* proxyModel READ proxyModel CONSTANT)
    Q_PROPERTY(SelectPresentProxyModel* selectModel READ selectModel CONSTANT)
    Q_PROPERTY(DiaporamaModel* diaporamaModel READ diaporamaModel CONSTANT)
    Q_PROPERTY(Player* gameMaster READ gameMaster CONSTANT)
    Q_PROPERTY(Player* characterOne READ characterOne CONSTANT)
    Q_PROPERTY(Player* characterTwo READ characterTwo CONSTANT)
    Q_PROPERTY(Player* characterThree READ characterThree CONSTANT)
    Q_PROPERTY(Player* characterFour READ characterFour CONSTANT)
    Q_PROPERTY(QString campaign READ campaign WRITE setCampaign NOTIFY campaignChanged)
    Q_PROPERTY(qreal maxSpeakingTime READ maxSpeakingTime NOTIFY maxSpeakingTimeChanged)
    Q_PROPERTY(bool table1 READ table1 CONSTANT)
    Q_PROPERTY(DiaporamaModel* carouselModel READ carouselModel CONSTANT)
    Q_PROPERTY(SortedModel* sortedModel READ sortedModel CONSTANT)
    Q_PROPERTY(PreviewController* previewCtrl READ previewCtrl CONSTANT)
public:
    explicit MainController(QObject* parent= nullptr);
    ~MainController();

    CharacterAvatarModel* avatarModel() const;

    Player* gameMaster() const;
    Player* characterOne() const;
    Player* characterTwo() const;
    Player* characterThree() const;
    Player* characterFour() const;
    SortedModel* sortedModel() const;
    PreviewController* previewCtrl() const;
    PresentProxyModel* proxyModel() const;
    SelectPresentProxyModel* selectModel() const;
    DiaporamaModel* diaporamaModel() const;
    bool table1() const;
    const QString& campaign() const;
    qreal maxSpeakingTime() const;
    DiaporamaModel* carouselModel() const;

    void setCampaign(const QString& newCampaign);

signals:
    void campaignChanged();
    void maxSpeakingTimeChanged();

private:
    std::unique_ptr<CharacterAvatarModel> m_avatarModel;
    std::unique_ptr<PresentProxyModel> m_proxyModel;
    std::unique_ptr<SelectPresentProxyModel> m_selectModel;
    std::unique_ptr<DiaporamaModel> m_diaporamaModel;
    std::unique_ptr<DiaporamaModel> m_carouselModel;
    std::unique_ptr<SortedModel> m_npcSortedModel;
    QString m_campaign;
    bool m_table1{false};
    std::unique_ptr<PreviewController> m_previewCtrl;
};

#endif // MAINCONTROLLER_H
