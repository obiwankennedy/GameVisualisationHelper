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
#include "haikumodel.h"

#include "utils/iohelper.h"

constexpr char const* PATH_DATA{"/home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/15_riz/haiku.json"};

HaikuModel::HaikuModel(QObject* parent) : QAbstractListModel(parent)
{
    m_haiku= IOHelper::readJsonArrayToStringList(PATH_DATA);

    qDebug() << m_haiku.size();
}

QVariant HaikuModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    return {};
}

int HaikuModel::rowCount(const QModelIndex& parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if(parent.isValid())
        return 0;

    return m_haiku.size();
}

QVariant HaikuModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role != Qt::DisplayRole)
        return {};

    return m_haiku[index.row()];
}
void HaikuModel::writeModel()
{
    IOHelper::writeStringListAsJsonArray(PATH_DATA, m_haiku);
}

void HaikuModel::addHaiku(const QString& haiku)
{
    beginInsertRows({}, m_haiku.size(), m_haiku.size());
    m_haiku.append(haiku);
    endInsertRows();
}
