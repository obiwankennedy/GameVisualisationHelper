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
#include "model/sortfiltermodel.h"
#include <QObject>
#include <QSortFilterProxyModel>
#include <memory>

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
