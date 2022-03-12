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
#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "model/charactermodel.h"
#include <QObject>
#include <QSortFilterProxyModel>
#include <memory>

#include "coretype.h"

class SortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString pattern READ pattern WRITE setPattern NOTIFY patternChanged)
    Q_PROPERTY(QString faction READ faction WRITE setFaction NOTIFY factionChanged)
    Q_PROPERTY(QString owner READ owner WRITE setOwner NOTIFY ownerChanged)
    Q_PROPERTY(QString clan READ clan WRITE setClan NOTIFY clanChanged)
    Q_PROPERTY(core::Gender gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(core::Table table READ TABLE WRITE setTable NOTIFY tableChanged)

public:
    SortFilterModel();

    const QString& pattern() const;
    void setPattern(const QString& newPattern);
    const QString& faction() const;
    void setFaction(const QString& newFaction);

    const QString& owner() const;
    void setOwner(const QString& newOwner);

    const QString& clan() const;
    void setClan(const QString& newClan);

    core::Gender gender() const;
    void setGender(core::Gender newGender);

    core::Table TABLE() const;
    void setTable(core::Table newTable);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

signals:
    void patternChanged();
    void factionChanged();
    void ownerChanged();
    void clanChanged();
    void genderChanged();
    void tableChanged();

private:
    QString m_pattern;
    QString m_faction;
    QString m_owner;
    QString m_clan;
    core::Gender m_gender= core::Gender::All;
    core::Table m_table= core::Table::All;
};

class CharacterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CharacterModel* model READ model CONSTANT)
    Q_PROPERTY(QStringList clanModel READ clanModel CONSTANT)
    Q_PROPERTY(QStringList factionModel READ factionModel CONSTANT)
    Q_PROPERTY(QStringList ownerModel READ ownerModel CONSTANT)
    Q_PROPERTY(SortFilterModel* filteredModel READ filteredModel CONSTANT)
public:
    explicit CharacterController(QObject* parent= nullptr);

    const QStringList ownerModel() const;
    CharacterModel* model() const;
    const QStringList clanModel() const;
    const QStringList factionModel() const;
    SortFilterModel* filteredModel() const;
    void setFilteredModel(const SortFilterModel& newFilteredModel);
    void saveModel() const;

signals:

    void filteredModelChanged();

private:
    std::unique_ptr<CharacterModel> m_model;
    std::unique_ptr<SortFilterModel> m_filteredModel;
    QStringList m_clanModel;
    QStringList m_factionModel;
};

#endif // CHARACTERCONTROLLER_H
