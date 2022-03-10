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
#include "diaporamamodel.h"
#include <QDir>

QStringList imageToList(const QString& path)
{
    QDir dir(path);

    auto imgs= dir.entryList({"*.jpg", "*.png", "*.gif", "*.ppm", "*.jpeg"}, QDir::Files | QDir::NoDotAndDotDot);

    QStringList result;

    std::transform(std::begin(imgs), std::end(imgs), std::back_inserter(result),
                   [path](const QString& img) { return QString("file://%1/%2").arg(path, img); });

    return result;
}

DiaporamaModel::DiaporamaModel(const QString& directory, QObject* parent) : QAbstractListModel(parent)
{
    m_data << imageToList(directory);
}

int DiaporamaModel::rowCount(const QModelIndex& parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if(parent.isValid())
        return 0;

    return m_data.size();
}

QVariant DiaporamaModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();

    QVariant var;

    if(role == Qt::DisplayRole || role == PathRole)
        var= m_data.at(index.row());
    else if(role == NameRole)
    {
        QFileInfo info(m_data.at(index.row()));
        var= info.baseName().replace("_", " ");
    }

    return var;
}

QHash<int, QByteArray> DiaporamaModel::roleNames() const
{
    return {{PathRole, "path"}, {NameRole, "name"}};
}
