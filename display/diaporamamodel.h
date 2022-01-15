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
#ifndef DIAPORAMAMODEL_H
#define DIAPORAMAMODEL_H

#include <QAbstractListModel>

class DiaporamaModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum CustomRole
    {
        PathRole= Qt::UserRole + 1,
    };
    Q_ENUM(CustomRole)
    explicit DiaporamaModel(QObject* parent= nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex& parent= QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role= Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QString m_directory;
    QStringList m_data;
};

#endif // DIAPORAMAMODEL_H
