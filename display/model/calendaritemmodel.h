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
#ifndef CALENDARITEMMODEL_H
#define CALENDARITEMMODEL_H

#include "coretype.h"
#include "qqmlregistration.h"
#include <QAbstractListModel>
#include <QColor>

struct CalendarItem
{
    QString m_title;
    QString m_desc;
    int m_startDay;
    int m_duration; // in days
    core::Table m_table;
    int m_row;
    QColor m_color;
    bool m_lock;
    QString m_image;
};

class CalendarItemModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum CustomRole
    {
        TitleRole= Qt::UserRole + 1,
        DescRole,
        StartRole,
        DurationRole,
        TableRole,
        RowRole,
        ColorRole,
        LockRole,
        ImageRole
    };
    Q_ENUM(CustomRole)
    explicit CalendarItemModel(QObject* parent= nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex& parent= QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role= Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& var, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    const std::vector<CalendarItem>& items() const;

public slots:
    void append(const QString& title, const QString& desc, int startDay, int duration, core::Table table, int row,
                QColor color, bool lock= false, const QString& image= {});

private:
    std::vector<CalendarItem> m_items;
};

#endif // CALENDARITEMMODEL_H
