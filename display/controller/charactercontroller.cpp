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
#include "charactercontroller.h"
#include "utils/iohelper.h"

constexpr char const* none{"none"};

CharacterController::CharacterController(QObject* parent)
    : QObject{parent}, m_model{new CharacterModel}, m_filteredModel{new SortFilterModel}
{
    IOHelper::fetchModel("/home/renaud/www/scripts/28_pnj_database/database.json",
                         "/home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/15_riz/additinal_data_npc.json",
                         m_model.get());
    m_filteredModel->setSourceModel(m_model.get());
}

void CharacterController::saveModel() const
{
    IOHelper::writeModel("/home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/15_riz/additinal_data_npc.json",
                         m_model.get());
}

const QStringList CharacterController::ownerModel() const
{
    QStringList list;
    list << none;
    list << m_model->ownerList();
    return list;
}

CharacterModel* CharacterController::model() const
{
    return m_model.get();
}

const QStringList CharacterController::clanModel() const
{
    QStringList list;
    list << none;
    list << m_model->clanList();
    return list;
}

const QStringList CharacterController::factionModel() const
{
    QStringList list;
    list << none;
    list << m_model->factionList();
    return list;
}

SortFilterModel* CharacterController::filteredModel() const
{
    return m_filteredModel.get();
}
