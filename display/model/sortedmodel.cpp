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
#include "sortedmodel.h"

SortedModel::SortedModel(QObject* parent) : QSortFilterProxyModel{parent}
{
    setDynamicSortFilter(true);
}

bool SortedModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
{
    // return left > right

    auto avatarpathLeft= source_left.siblingAtColumn(0).data(Qt::DisplayRole).toString();
    auto nameLeft= source_left.siblingAtColumn(1).data(Qt::DisplayRole).toString();
    auto clanLeft= source_left.siblingAtColumn(5).data(Qt::DisplayRole).toString();

    auto avatarpathRight= source_right.siblingAtColumn(0).data(Qt::DisplayRole).toString();
    auto nameRight= source_right.siblingAtColumn(1).data(Qt::DisplayRole).toString();
    auto clanRight= source_right.siblingAtColumn(5).data(Qt::DisplayRole).toString();

    if(avatarpathLeft.isEmpty() && !avatarpathRight.isEmpty())
    {
        return false;
    }
    else if(!avatarpathLeft.isEmpty() && avatarpathRight.isEmpty())
    {
        return false;
    }
    else
    {
        if(clanRight == clanLeft)
        {
            return nameLeft < nameRight;
        }
        else
        {
            return clanLeft < clanRight;
        }
    }
}
