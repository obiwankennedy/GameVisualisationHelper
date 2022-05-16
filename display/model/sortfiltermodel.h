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
#ifndef SORTFILTERMODEL_H
#define SORTFILTERMODEL_H

#include <QSortFilterProxyModel>

#include "coretype.h"

class SortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString pattern READ pattern WRITE setPattern NOTIFY patternChanged)
    Q_PROPERTY(QString ignoredPattern READ ignoredPattern WRITE setIgnoredPattern NOTIFY ignoredPatternChanged)
    Q_PROPERTY(QString faction READ faction WRITE setFaction NOTIFY factionChanged)
    Q_PROPERTY(QString owner READ owner WRITE setOwner NOTIFY ownerChanged)
    Q_PROPERTY(QString clan READ clan WRITE setClan NOTIFY clanChanged)
    Q_PROPERTY(core::Gender gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(core::Table table READ TABLE WRITE setTable NOTIFY tableChanged)
    Q_PROPERTY(core::Status status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(bool hideDead READ hideDead WRITE setHideDead NOTIFY hideDeadChanged)
    Q_PROPERTY(bool hideNoAvatar READ hideNoAvatar WRITE setHideNoAvatar NOTIFY hideNoAvatarChanged)

public:
    SortFilterModel(QObject* parent= nullptr);

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

    const QString& ignoredPattern() const;
    void setIgnoredPattern(const QString& newIgnoredPattern);

    core::Status status() const;
    void setStatus(core::Status newStatus);

    bool hideNoAvatar() const;
    void setHideNoAvatar(bool newHideNoAvatar);

    bool hideDead() const;
    void setHideDead(bool newHideDead);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

signals:
    void patternChanged();
    void factionChanged();
    void ownerChanged();
    void clanChanged();
    void genderChanged();
    void tableChanged();

    void ignoredPatternChanged();

    void statusChanged();

    void hideNoAvatarChanged();

    void hideDeadChanged();

private:
    QString m_pattern;
    QString m_faction;
    QString m_owner;
    QString m_clan;
    core::Gender m_gender= core::Gender::All;
    core::Table m_table= core::Table::All;
    QString m_ignoredPattern;
    core::Status m_status{core::Status::All};
    bool m_hideNoAvatar{false};
    bool m_hideDead{false};
};
#endif // SORTFILTERMODEL_H
