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
#include "iohelper.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>

#include "model/calendaritemmodel.h"
#include "model/charactermodel.h"

namespace IOHelper
{
namespace
{
constexpr char const* CALENDAR_PATH{"/home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/15_riz/calendar.json"};
}
void fetchModel(const QString& database, const QString& internalData, CharacterModel* model)
{
    QHash<QString, NonPlayableCharacter*> npcs;

    {
        QFile file(database);
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "can't open database";
            return;
        }
        auto jsondata= file.readAll();

        QJsonDocument doc= QJsonDocument::fromJson(jsondata);
        auto array= doc.array();
        for(auto val : array)
        {
            auto obj= val.toObject();
            auto name= obj["name"].toString();
            NonPlayableCharacter* current= nullptr;
            if(npcs.contains(name))
            {
                current= npcs[name];
            }
            else
            {
                current= new NonPlayableCharacter();
                npcs[name]= current;
            }

            current->setName(name);
            auto desc= current->description();
            auto newDesc= obj["desc"].toString();

            if(desc.isEmpty() && !newDesc.isEmpty())
                current->setDescription(obj["desc"].toString());
            else if(!newDesc.isEmpty())
                current->setDescription(QString("%1\n%2").arg(desc, obj["desc"].toString()));

            auto g= obj["genre"].toString().startsWith("F", Qt::CaseInsensitive) ? core::Gender::Feminin :
                                                                                   core::Gender::Masculin;
            current->setGender(g);
            current->setClan(obj["clan"].toString());

            auto owners= current->owners();
            owners << obj["owner"].toString().split(",");
            current->setOwners(owners);

            auto tIdx= obj["table"].toInt();
            auto table= tIdx == 0 ? core::Table::All : tIdx == 1 ? core::Table::Table1 : core::Table::Table2;
            current->setTable(table);
        }
    }

    {
        QFile file(internalData);
        if(file.open(QIODevice::ReadOnly))
        {
            auto jsondata= file.readAll();
            QJsonDocument doc= QJsonDocument::fromJson(jsondata);
            auto array= doc.array();
            for(auto val : array)
            {
                auto obj= val.toObject();
                auto name= obj["name"].toString();
                NonPlayableCharacter* current= nullptr;
                if(npcs.contains(name))
                {
                    current= npcs[name];
                }
                else
                {
                    current= new NonPlayableCharacter();
                    npcs[name]= current;
                }

                current->setAge(obj["age"].toInt());
                current->setUrlAvatar(obj["avatarpath"].toString());
                current->setFaction(obj["faction"].toString());
                current->setSamuraiStatus(obj["status"].toBool());

                auto g= obj["genre"].toVariant().value<core::Gender>();
                current->setGender(g);

                auto clan= obj["clan"].toString();
                if(!clan.isEmpty())
                    current->setClan(clan);

                auto desc= current->description();
                auto newDesc= obj["desc"].toString();

                auto sheetObj= obj["sheet"].toObject();
                QHash<QString, QString> sheet;

                for(const auto& key : sheetObj.keys())
                {
                    auto val= sheetObj[key].toString();
                    sheet.insert(key, val);
                }
                current->setSheetProperties(sheet);

                if(desc.isEmpty() && !newDesc.isEmpty())
                    current->setDescription(newDesc);
                else if(newDesc.contains(desc))
                    current->setDescription(newDesc);
                else if(!newDesc.isEmpty())
                    current->setDescription(QString("%1\n%2").arg(desc, obj["desc"].toString()));

                current->setTags(obj["tags"].toString().split(","));
            }
        }
    }

    auto vals= npcs.values();
    model->resetModel(vals);
}

void writeModel(const QString& internalData, CharacterModel* model)
{
    auto const& vec= model->characters();

    QJsonArray array;
    for(auto const& item : vec)
    {
        QJsonObject obj;

        obj["name"]= item->name();
        obj["age"]= item->age();
        obj["avatarpath"]= item->urlAvatar();
        obj["desc"]= item->description();
        obj["genre"]= QJsonValue::fromVariant(QVariant::fromValue(item->gender()));
        obj["clan"]= item->clan();
        obj["faction"]= item->faction();
        obj["tags"]= item->tags().join(", ");
        obj["status"]= item->isSamurai();
        auto sheet= item->sheetProperties();
        QVariantHash varhash;
        auto keys= sheet.keys();
        for(auto const& key : keys)
        {
            auto val= sheet[key];
            varhash.insert(key, QVariant(val));
        }

        obj["sheet"]= QJsonObject::fromVariantHash(varhash);

        array.append(obj);
    }
    QJsonDocument doc;
    doc.setArray(array);

    QSaveFile file(internalData);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
        file.commit();
    }
}

void writeStringListAsJsonArray(const QString& file, QStringList data)
{
    QSaveFile dataFile(file);
    if(!dataFile.open(QIODevice::WriteOnly))
        return;

    QJsonDocument doc;
    QJsonArray array= QJsonArray::fromStringList(data);
    doc.setArray(array);

    dataFile.write(doc.toJson());
    dataFile.commit();
}

QStringList readJsonArrayToStringList(const QString& filepath)
{
    QFile file(filepath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return {};
    }

    auto data= file.readAll();
    QJsonDocument doc= QJsonDocument::fromJson(data);
    auto array= doc.array();

    QStringList list;
    std::transform(std::begin(array), std::end(array), std::back_inserter(list),
                   [](const QJsonValue& val) { return val.toString(); });

    return list;
}

void fetchCalendarModel(CalendarItemModel* model)
{
    QFile file(CALENDAR_PATH);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "can't open calendar path";
        return;
    }
    auto jsondata= file.readAll();

    QJsonDocument doc= QJsonDocument::fromJson(jsondata);
    auto array= doc.array();
    for(auto const& val : array)
    {
        auto obj= val.toObject();
        model->append(obj["title"].toString(), obj["desc"].toString(), obj["start"].toInt(), obj["dura"].toInt(),
                      static_cast<core::Table>(obj["table"].toInt()), obj["row"].toInt(),
                      QColor(obj["color"].toString()), obj["lock"].toBool(), obj["image"].toString());
    }
}

void writeCalendarModel(CalendarItemModel* model)
{
    auto const& vec= model->items();

    QJsonArray array;
    for(auto const& item : vec)
    {
        QJsonObject obj;

        obj["title"]= item.m_title;
        obj["desc"]= item.m_desc;
        obj["start"]= item.m_startDay;
        obj["dura"]= item.m_duration;
        obj["table"]= static_cast<int>(item.m_table);
        obj["row"]= item.m_row;
        obj["color"]= item.m_color.name();
        obj["lock"]= item.m_lock;
        obj["image"]= item.m_image;

        array.append(obj);
    }
    QJsonDocument doc;
    doc.setArray(array);

    QSaveFile file(CALENDAR_PATH);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(doc.toJson());
        file.commit();
    }
}
} // namespace IOHelper
