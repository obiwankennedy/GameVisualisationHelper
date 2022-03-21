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
#include "dragabletableview.h"

#include <QDrag>
#include <QMouseEvent>

DragableTableView::DragableTableView(QWidget* parent) : QTableView(parent)
{
    setAcceptDrops(true);
    setDragEnabled(true);
    setDropIndicatorShown(true);
    setDefaultDropAction(Qt::MoveAction);
    setDragDropMode(QAbstractItemView::DragOnly);
}

void DragableTableView::startDrag(Qt::DropActions supportedActions)
{
    auto drag= new QDrag(this);
    QModelIndexList indexes= selectionModel()->selectedRows();

    QMimeData* mimeData= model()->mimeData(indexes);
    if(nullptr == mimeData)
    {
        delete drag;
        return;
    }

    drag->setMimeData(mimeData);
    Qt::DropAction defaultDropAction= Qt::MoveAction;

    drag->exec(supportedActions, defaultDropAction);
}

void DragableTableView::mouseMoveEvent(QMouseEvent* event)
{
    QModelIndex tmp= indexAt(event->pos());

    QTableView::mousePressEvent(event);

    if((event->buttons() == Qt::LeftButton) && (tmp.isValid()))
    {
        startDrag(Qt::MoveAction);
    }
}
