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
#ifndef CHARACTERMODEL_H
#define CHARACTERMODEL_H

#include "coretype.h"
#include <QAbstractTableModel>
#include <QHash>
#include <QPixmap>

class NonPlayableCharacter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(core::Gender gender READ gender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(QString clan READ clan WRITE setClan NOTIFY clanChanged)
    Q_PROPERTY(QString faction READ faction WRITE setFaction NOTIFY factionChanged)
    Q_PROPERTY(QStringList tags READ tags WRITE setTags NOTIFY tagsChanged)
    Q_PROPERTY(core::Table table READ table WRITE setTable NOTIFY tableChanged)
    Q_PROPERTY(QStringList owners READ owners WRITE setOwners NOTIFY ownersChanged)
    Q_PROPERTY(bool local READ local WRITE setLocal NOTIFY localChanged)
    Q_PROPERTY(QString urlAvatar READ urlAvatar WRITE setUrlAvatar NOTIFY urlAvatarChanged)

public:
    const QStringList& owners() const;
    void setOwners(const QStringList& newOwner);

    const core::Table& table() const;
    void setTable(const core::Table& newTable);

    const QStringList& tags() const;
    void setTags(const QStringList& newTags);

    const QString& faction() const;
    void setFaction(const QString& newFaction);

    core::Gender gender() const;
    void setGender(core::Gender newGender);

    int age() const;
    void setAge(int newAge);

    const QString& description() const;
    void setDescription(const QString& newDescription);

    const QString& name() const;
    void setName(const QString& newName);

    bool local() const;
    void setLocal(bool newLocal);

    const QString& clan() const;
    void setClan(const QString& newClan);

    const QString& urlAvatar() const;
    void setUrlAvatar(const QString& newUrlAvatar);

signals:
    void ownersChanged();
    void tableChanged();
    void tagsChanged();
    void factionChanged();
    void genderChanged();
    void ageChanged();
    void descriptionChanged();
    void nameChanged();

    void localChanged();

    void clanChanged();

    void urlAvatarChanged();

private:
    QStringList m_owners;
    core::Table m_table;
    QStringList m_tags;
    QString m_faction;
    core::Gender m_gender;
    int m_age;
    QString m_description;
    QString m_name;
    bool m_local= true;
    QString m_clan;
    QString m_urlAvatar;
};

class CharacterModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Role
    {
        NameRole= Qt::UserRole + 1,
        DescRole,
        AgeRole,
        AvatarUrlRole,
        GenderRole,
        ClanRole,
        FactionRole,
        TableRole,
        OwnerRole,
        TagsRole
    };
    explicit CharacterModel(QObject* parent= nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role= Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex& parent= QModelIndex()) const override;
    int columnCount(const QModelIndex& parent= QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role= Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex& index, const QVariant& value, int role= Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QStringList clanList() const;
    QStringList ownerList() const;
    QStringList factionList() const;

    void resetModel(QList<NonPlayableCharacter*> values);

    const std::vector<std::unique_ptr<NonPlayableCharacter>>& characters() const;
    void setImage(const QPixmap& map, const QString& name);

    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<std::unique_ptr<NonPlayableCharacter>> m_characters;
    QHash<QString, QPixmap> m_avatars;
    QStringList m_columns;
};

#endif // CHARACTERMODEL_H
