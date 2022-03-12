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
constexpr char const* toutes{"toutes"};

SortFilterModel::SortFilterModel()
{
    setDynamicSortFilter(true);
    connect(this, &SortFilterModel::patternChanged, this, &SortFilterModel::invalidateFilter);
    connect(this, &SortFilterModel::factionChanged, this, &SortFilterModel::invalidateFilter);
    connect(this, &SortFilterModel::ownerChanged, this, &SortFilterModel::invalidateFilter);
    connect(this, &SortFilterModel::clanChanged, this, &SortFilterModel::invalidateFilter);
    connect(this, &SortFilterModel::genderChanged, this, &SortFilterModel::invalidateFilter);
    connect(this, &SortFilterModel::tableChanged, this, &SortFilterModel::invalidateFilter);
}

const QString& SortFilterModel::pattern() const
{
    return m_pattern;
}

void SortFilterModel::setPattern(const QString& newPattern)
{
    if(m_pattern == newPattern)
        return;
    m_pattern= newPattern;
    emit patternChanged();
}

const QString& SortFilterModel::faction() const
{
    return m_faction;
}

void SortFilterModel::setFaction(const QString& newFaction)
{
    if(m_faction == newFaction)
        return;
    m_faction= newFaction;
    emit factionChanged();
}

const QString& SortFilterModel::owner() const
{
    return m_owner;
}

void SortFilterModel::setOwner(const QString& newOwner)
{
    if(m_owner == newOwner)
        return;
    m_owner= newOwner;
    emit ownerChanged();
}

const QString& SortFilterModel::clan() const
{
    return m_clan;
}

void SortFilterModel::setClan(const QString& newClan)
{
    if(m_clan == newClan)
        return;
    m_clan= newClan;
    emit clanChanged();
}

core::Gender SortFilterModel::gender() const
{
    return m_gender;
}

void SortFilterModel::setGender(core::Gender newGender)
{
    if(m_gender == newGender)
        return;
    m_gender= newGender;
    emit genderChanged();
}

core::Table SortFilterModel::TABLE() const
{
    return m_table;
}

void SortFilterModel::setTable(core::Table newTable)
{
    if(m_table == newTable)
        return;
    m_table= newTable;
    emit tableChanged();
}

bool isCorrectTable(core::Table wish, const QString& text)
{
    if(wish == core::Table::All)
        return true;
    else if(text == toutes)
        return true;
    else if(text == "Table1" && wish == core::Table::Table1)
        return true;
    else if(text == "Table2" && wish == core::Table::Table2)
        return true;
    else
        return false;
}

bool isCorrectGender(core::Gender wish, const QChar& gender)
{
    if(wish == core::Gender::All)
        return true;
    else if(gender == 'M' && wish == core::Gender::Masculin)
        return true;
    else if(gender == 'F' && wish == core::Gender::Feminin)
        return true;
    else
        return false;
}

bool SortFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    if(m_pattern.isEmpty() && m_table == core::Table::All && m_gender == core::Gender::All && m_clan.isEmpty()
       && m_faction.isEmpty() && m_owner.isEmpty())
        return true;

    auto nameIndex= sourceModel()->index(sourceRow, 1, sourceParent).data().toString();
    auto descIndex= sourceModel()->index(sourceRow, 2, sourceParent).data().toString();
    auto genderIndex= sourceModel()->index(sourceRow, 3, sourceParent).data().toChar();
    auto clanIndex= sourceModel()->index(sourceRow, 5, sourceParent).data().toString();
    auto factionIndex= sourceModel()->index(sourceRow, 6, sourceParent).data().toString();
    auto tableIndex= sourceModel()->index(sourceRow, 7, sourceParent).data().toString();
    auto ownerIndex= sourceModel()->index(sourceRow, 8, sourceParent).data().toString();
    auto tagsIndex= sourceModel()->index(sourceRow, 9, sourceParent).data().toString();

    auto correctGender= isCorrectGender(m_gender, genderIndex);
    auto correctTable= isCorrectTable(m_table, tableIndex);

    return (nameIndex.contains(m_pattern) | descIndex.contains(m_pattern) | tagsIndex.contains(m_pattern))
           & correctGender & (m_clan.isEmpty() ? true : clanIndex == m_clan)
           & (m_faction.isEmpty() ? true : factionIndex == m_faction)
           & (m_owner.isEmpty() ? true : ownerIndex.contains(m_owner)) & correctTable;
}

// end of sort filter

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
