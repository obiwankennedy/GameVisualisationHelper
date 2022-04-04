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
#include "calendaritemmodel.h"

CalendarItemModel::CalendarItemModel(QObject* parent) : QAbstractListModel(parent) {}

int CalendarItemModel::rowCount(const QModelIndex& parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if(parent.isValid())
        return 0;

    return m_items.size();
}

QVariant CalendarItemModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();

    auto const& item= m_items[index.row()];

    auto realRole= role;
    if(role < Qt::UserRole)
        realRole= Qt::UserRole + index.column();

    QVariant res;
    switch(realRole)
    {
    case TitleRole:
        res= item.m_title;
        break;
    case DescRole:
        res= item.m_desc;
        break;
    case StartRole:
        res= item.m_startDay;
        break;
    case DurationRole:
        res= item.m_duration;
        break;
    case TableRole:
        res= QVariant::fromValue(item.m_table);
        break;
    case RowRole:
        res= item.m_row;
        break;
    case ColorRole:
        res= QVariant::fromValue(item.m_color);
        break;
    case LockRole:
        res= item.m_lock;
        break;
    case ImageRole:
        res= item.m_image;
        break;
    }
    return res;
}

bool CalendarItemModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(data(index, role) != value)
    {
        auto& item= m_items[index.row()];

        switch(role)
        {
        case TitleRole:
            item.m_title= value.toString();
            break;
        case DescRole:
            item.m_desc= value.toString();
            break;
        case StartRole:
            if(!item.m_lock)
                item.m_startDay= value.toInt();
            break;
        case DurationRole:
            if(!item.m_lock)
                item.m_duration= value.toInt();
            break;
        case TableRole:
            item.m_table= value.value<core::Table>();
            break;
        case RowRole:
        {
            auto v= value.toInt();
            if(v < 0)
                v= 0;
            item.m_row= v;
        }
        break;
        case ColorRole:
            item.m_color= value.value<QColor>();
            break;
        case LockRole:
            qDebug() << "locK" << value.toBool();
            item.m_lock= value.toBool();
            break;
        case ImageRole:
            item.m_image= value.toString();
            break;
        }

        emit dataChanged(index, index, QVector<int>{role});
        return true;
    }
    return false;
}

void CalendarItemModel::append(const QString& title, const QString& desc, int startDay, int duration, core::Table table,
                               int row, QColor color, bool lock, const QString& image)
{
    beginInsertRows({}, m_items.size(), m_items.size());
    m_items.push_back({title, desc, startDay, duration, table, row, color, lock, image});
    endInsertRows();
}

QHash<int, QByteArray> CalendarItemModel::roleNames() const
{
    return {{TitleRole, "title"},       {DescRole, "desc"},   {StartRole, "start"},
            {DurationRole, "duration"}, {TableRole, "table"}, {RowRole, "row"},
            {ColorRole, "color"},       {LockRole, "lock"},   {ImageRole, "image"}};
}

const std::vector<CalendarItem>& CalendarItemModel::items() const
{
    return m_items;
}
