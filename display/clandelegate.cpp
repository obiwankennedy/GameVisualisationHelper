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
#include "clandelegate.h"

#include <QDebug>
#include <QPainter>

QString toLower(const QString& up)
{
    return up.toLower();
}

ClanDelegate::ClanDelegate()
{
    m_images.insert(toLower("Blaireau"), QPixmap(":/resources/L5RRiz/symbols/185px-Badger.png"));
    m_images.insert(toLower("Chauve-Souris"), QPixmap(":/resources/L5RRiz/symbols/185px-Bat.png"));
    m_images.insert(toLower("Sanglier"), QPixmap(":/resources/L5RRiz/symbols/185px-Boar.png"));
    m_images.insert(toLower("Mille-pattes"), QPixmap(":/resources/L5RRiz/symbols/185px-Centipede.png"));
    m_images.insert(toLower("Libellule"), QPixmap(":/resources/L5RRiz/symbols/185px-Dragonfly.png"));
    m_images.insert(toLower("Faucon"), QPixmap(":/resources/L5RRiz/symbols/185px-Falcon.png"));
    m_images.insert(toLower("Moineau"), QPixmap(":/resources/L5RRiz/symbols/185px-Sparrow.png"));
    m_images.insert(toLower("Tortue"), QPixmap(":/resources/L5RRiz/symbols/185px-Tortoise.png"));
    m_images.insert(toLower("Guepe"), QPixmap(":/resources/L5RRiz/symbols/185px-Wasp.png"));
    m_images.insert(toLower("Guêpe"), QPixmap(":/resources/L5RRiz/symbols/185px-Wasp.png"));
    m_images.insert(toLower("Crabe"), QPixmap(":/resources/L5RRiz/symbols/crab.png"));
    m_images.insert(toLower("Grue"), QPixmap(":/resources/L5RRiz/symbols/crane.png"));
    m_images.insert(toLower("Dragon"), QPixmap(":/resources/L5RRiz/symbols/dragon.png"));
    m_images.insert(toLower("Impériaux"), QPixmap(":/resources/L5RRiz/symbols/empire.png"));
    m_images.insert(toLower("Lievre"), QPixmap(":/resources/L5RRiz/symbols/lievre.png"));
    m_images.insert(toLower("Lion"), QPixmap(":/resources/L5RRiz/symbols/lion.png"));
    m_images.insert(toLower("Mante"), QPixmap(":/resources/L5RRiz/symbols/mante.png"));
    m_images.insert(toLower("Singe"), QPixmap(":/resources/L5RRiz/symbols/monkey.png"));
    m_images.insert(toLower("Boeuf"), QPixmap(":/resources/L5RRiz/symbols/ox.png"));
    m_images.insert(toLower("Renard"), QPixmap(":/resources/L5RRiz/symbols/fox.png"));
    m_images.insert(toLower("Phénix"), QPixmap(":/resources/L5RRiz/symbols/phenix.png"));
    m_images.insert(toLower("Ronin"), QPixmap(":/resources/L5RRiz/symbols/ronin.png"));
    m_images.insert(toLower("Scorpion"), QPixmap(":/resources/L5RRiz/symbols/scorpion.png"));
    m_images.insert(toLower("Araignée"), QPixmap(":/resources/L5RRiz/symbols/spider.png"));
    m_images.insert(toLower("Licorne"), QPixmap(":/resources/L5RRiz/symbols/unicorn.png"));
}

void ClanDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{

    auto val= index.data().toString().toLower();

    if(m_images.contains(val))
    {
        auto rect= option.rect;
        auto pix= m_images[val];
        QRect vRect;
        if(rect.height() < rect.width())
        {
            pix= pix.scaledToHeight(rect.height());
            vRect= {rect.x() + ((rect.width() - rect.height()) / 2), rect.y(), rect.height(), rect.height()};
        }
        else
        {
            pix= pix.scaledToWidth(rect.width());
            vRect= {rect.x(), rect.y() + ((rect.height() - rect.width()) / 2), rect.width(), rect.width()};
        }
        painter->drawPixmap(vRect, pix, pix.rect());
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}
