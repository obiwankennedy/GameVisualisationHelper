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
#include "charactermodel.h"

#include <QColor>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QVariant>
#include <set>

QPixmap readImage(const QString& path, CharacterModel* model, const QString& name)
{
    if(path.isEmpty())
        return {};

    QUrl url= QUrl::fromUserInput(path);
    QPixmap map;
    if(url.isLocalFile())
    {
        map= QPixmap{url.toLocalFile()};
    }
    else
    {
        QNetworkAccessManager* man= new QNetworkAccessManager;
        QObject::connect(man, &QNetworkAccessManager::finished, model, [model, name, man](QNetworkReply* reply) {
            auto data= reply->readAll();
            QPixmap map= QPixmap::fromImage(QImage::fromData(data));
            if(!map.isNull())
                model->setImage(map, name);
            man->deleteLater();
        });
        man->get(QNetworkRequest(url));
    }

    return map;
}

const QStringList& NonPlayableCharacter::owners() const
{
    return m_owners;
}

void NonPlayableCharacter::setOwners(const QStringList& newOwner)
{
    if(m_owners == newOwner)
        return;
    m_owners.clear();
    std::transform(std::begin(newOwner), std::end(newOwner), std::back_inserter(m_owners),
                   [](const QString& item) { return item.trimmed(); });
    emit ownersChanged();
}

const core::Table& NonPlayableCharacter::table() const
{
    return m_table;
}

void NonPlayableCharacter::setTable(const core::Table& newTable)
{
    if(m_table == newTable)
        return;
    m_table= newTable;
    emit tableChanged();
}

const QString& NonPlayableCharacter::urlAvatar() const
{
    return m_urlAvatar;
}

void NonPlayableCharacter::setUrlAvatar(const QString& newUrlAvatar)
{
    if(m_urlAvatar == newUrlAvatar)
        return;
    m_urlAvatar= newUrlAvatar;
    emit urlAvatarChanged();
}

const QStringList& NonPlayableCharacter::tags() const
{
    return m_tags;
}

void NonPlayableCharacter::setTags(const QStringList& newTags)
{
    if(m_tags == newTags)
        return;

    m_tags.clear();
    std::transform(std::begin(newTags), std::end(newTags), std::back_inserter(m_tags),
                   [](const QString& item) { return item.trimmed(); });

    emit tagsChanged();
}

const QString& NonPlayableCharacter::faction() const
{
    return m_faction;
}

void NonPlayableCharacter::setFaction(const QString& newFaction)
{
    if(m_faction == newFaction)
        return;
    m_faction= newFaction;
    emit factionChanged();
}

core::Gender NonPlayableCharacter::gender() const
{
    return m_gender;
}

void NonPlayableCharacter::setGender(core::Gender newGender)
{
    if(m_gender == newGender)
        return;
    m_gender= newGender;
    emit genderChanged();
}

int NonPlayableCharacter::age() const
{
    return m_age;
}

void NonPlayableCharacter::setAge(int newAge)
{
    if(m_age == newAge)
        return;
    m_age= newAge;
    emit ageChanged();
}

const QString& NonPlayableCharacter::description() const
{
    return m_description;
}

void NonPlayableCharacter::setDescription(const QString& newDescription)
{
    if(m_description == newDescription)
        return;
    m_description= newDescription;
    emit descriptionChanged();
}

const QString& NonPlayableCharacter::name() const
{
    return m_name;
}

void NonPlayableCharacter::setName(const QString& newName)
{
    if(m_name == newName)
        return;
    m_name= newName;
    emit nameChanged();
}

bool NonPlayableCharacter::local() const
{
    return m_local;
}

void NonPlayableCharacter::setLocal(bool newLocal)
{
    if(m_local == newLocal)
        return;
    m_local= newLocal;
    emit localChanged();
}

const QString& NonPlayableCharacter::clan() const
{
    return m_clan;
}

void NonPlayableCharacter::setClan(const QString& newClan)
{
    if(m_clan == newClan)
        return;
    m_clan= newClan;
    emit clanChanged();
}
// END OF NONPLAYABLE CHARACTER

CharacterModel::CharacterModel(QObject* parent)
    : QAbstractTableModel(parent), m_columns{tr("Avatar"), tr("Name"),    tr("Description"), tr("Gender"), tr("Age"),
                                             tr("Clan"),   tr("Faction"), tr("Table"),       tr("Owner"),  tr("Tags")}
{
}

QVariant CharacterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return m_columns[section];
    }
    else
        return {};
}

int CharacterModel::rowCount(const QModelIndex& parent) const
{
    if(parent.isValid())
        return 0;

    return m_characters.size();
}

int CharacterModel::columnCount(const QModelIndex& parent) const
{
    if(parent.isValid())
        return 0;

    return m_columns.size();
}

QVariant CharacterModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return QVariant();

    auto const& npc= m_characters[index.row()];

    if(role == Qt::DecorationRole && index.column() == 0)
    {
        QVariant res;
        if(m_avatars.contains(npc->name()))
            res= QVariant::fromValue(m_avatars[npc->name()].scaledToHeight(60));
        return res;
    }
    if(role == Qt::BackgroundRole && index.column() == 3)
    {

        QVariant res;
        switch(npc->gender())
        {
        case core::Gender::All:
            break;
        case core::Gender::Feminin:
            res= QVariant::fromValue(QColor("#DDA0DD"));
            break;
        case core::Gender::Masculin:
            res= QVariant::fromValue(QColor("#00BFFF"));
            break;
        case core::Gender::Unknown:
            res= QVariant::fromValue(QColor(Qt::gray));
            break;
        }
        return res;
    }

    if(role == Qt::TextAlignmentRole)
    {
        static QList<int> centerCol{3, 4, 5, 6, 7, 8};
        if(centerCol.contains(index.column()))
            return Qt::AlignCenter;
    }

    QSet<int> allowedRole{Qt::DisplayRole, Qt::EditRole};

    if(!allowedRole.contains(role))
        return {};

    QVariant res;
    switch(index.column())
    {
    case 0:
        res= npc->urlAvatar();
        break;
    case 1:
        res= npc->name();
        break;
    case 2:
        res= npc->description();
        break;
    case 3:
        switch(npc->gender())
        {
        case core::Gender::All:
            break;
        case core::Gender::Feminin:
            res= QChar('F');
            break;
        case core::Gender::Masculin:
            res= QChar('M');
            break;
        case core::Gender::Unknown:
            res= QChar('U');
            break;
        }
        break;
    case 4:
        res= npc->age();
        break;
    case 5:
        res= npc->clan();
        break;
    case 6:
        res= npc->faction();
        break;
    case 7:
        switch(npc->table())
        {
        case core::Table::All:
            res= QStringLiteral("Toutes");
            break;
        case core::Table::Table1:
            res= QStringLiteral("Table1");
            break;
        case core::Table::Table2:
            res= QStringLiteral("Table2");
            break;
        }
        break;
    case 8:
        res= npc->owners().join(",");
        break;
    case 9:
        res= npc->tags().join(",");
        break;
    }

    return res;
}

bool CharacterModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(data(index, role) != value)
    {
        auto& npc= m_characters[index.row()];

        switch(index.column())
        {
        case 0:
            npc->setUrlAvatar(value.toString());
            break;
        case 1:
            break;
        case 2:
            npc->setDescription(value.toString());
            break;
        case 3:
        {
            auto c= value.toChar();
            npc->setGender(c == QChar('F') ? core::Gender::Feminin :
                                             c == QChar('M') ? core::Gender::Masculin : core::Gender::Unknown);
        }
        break;
        case 4:
            npc->setAge(value.toInt());
            break;
        case 5:
            npc->setClan(value.toString());
            break;
        case 6:
            npc->setFaction(value.toString());
            break;
        case 7:
        {
            auto table= static_cast<core::Table>(value.toInt());
            npc->setTable(table == core::Table::All ?
                              core::Table::All :
                              table == core::Table::Table1 ? core::Table::Table1 : core::Table::Table2);
        }

        break;
        case 9:
            npc->setTags(value.toString().split(","));
            break;
        }

        emit dataChanged(index, index, QVector<int>{role});
        return true;
    }
    return false;
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex& index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    QList<int> readOnlyColumn{1, 3, 5, 7, 8};

    if(readOnlyColumn.contains(index.column()))
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    else
        return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QStringList CharacterModel::clanList() const
{
    std::set<QString> set;
    std::transform(std::begin(m_characters), std::end(m_characters), std::inserter(set, std::begin(set)),
                   [](const std::unique_ptr<NonPlayableCharacter>& character) { return character->clan(); });

    set.erase(QString());
    set.erase(QString(""));

    QStringList list{std::begin(set), std::end(set)};
    std::sort(std::begin(list), std::end(list));
    return list;
}

QStringList CharacterModel::ownerList() const
{
    std::set<QString> set;
    std::for_each(std::begin(m_characters), std::end(m_characters),
                  [&set](const std::unique_ptr<NonPlayableCharacter>& character) {
                      auto owners= character->owners();
                      for(auto const& o : owners)
                      {
                          set.insert(o);
                      }
                  });

    set.erase(QString());
    set.erase(QString(""));

    QStringList list{std::begin(set), std::end(set)};
    std::sort(std::begin(list), std::end(list));
    return list;
}

QStringList CharacterModel::factionList() const
{
    std::set<QString> set;
    std::transform(std::begin(m_characters), std::end(m_characters), std::inserter(set, std::begin(set)),
                   [](const std::unique_ptr<NonPlayableCharacter>& character) { return character->clan(); });

    set.erase(QString());
    set.erase(QString(""));

    QStringList list{std::begin(set), std::end(set)};

    std::sort(std::begin(list), std::end(list));
    return list;
}

void CharacterModel::resetModel(QList<NonPlayableCharacter*> values)
{
    beginResetModel();
    m_characters.clear();

    for(auto& val : values)
    {
        std::unique_ptr<NonPlayableCharacter> p(val);
        QPixmap map= readImage(p->urlAvatar(), this, p->name());
        if(!map.isNull())
            m_avatars.insert(p->name(), map);
        m_characters.push_back(std::move(p));
    }
    endResetModel();
}

const std::vector<std::unique_ptr<NonPlayableCharacter>>& CharacterModel::characters() const
{
    return m_characters;
}

void CharacterModel::setImage(const QPixmap& map, const QString& name)
{
    if(!map.isNull())
        m_avatars.insert(name, map);
}
