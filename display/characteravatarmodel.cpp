#include "characteravatarmodel.h"

#include "character.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

CharacterAvatarModel::CharacterAvatarModel(QObject* parent) : QAbstractItemModel(parent) {}

QVariant CharacterAvatarModel::data(const QModelIndex& index, int role) const
{
    if(!index.isValid())
        return {};

    QVariant var;
    auto item= m_persons[index.row()];

    switch(role)
    {
    case Qt::EditRole:
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 0:
            var= QVariant::fromValue(item->name());
            break;
        case 1:
            var= QVariant::fromValue(item->playerName());
            break;
        case 2:
            var= QVariant::fromValue(item->imgId());
            break;
        case 3:
            var= QVariant::fromValue(item->campaign());
            break;
        case 4:
            var= QVariant::fromValue(item->color());
            break;
        }
        break;
    case Name:
        var= QVariant::fromValue(item->name());
        break;
    case PlayerName:
        var= QVariant::fromValue(item->playerName());
        break;
    case ImageId:
        var= QVariant::fromValue(item->imgId());
        break;
    case IsSpeaking:
        var= QVariant::fromValue(item->isSpeaking());
        break;
    case Campaign:
        var= QVariant::fromValue(item->campaign());
        break;
    case SpeakingTime:
        var= QVariant::fromValue(item->speakingTime());
        break;
    case Color:
        var= QVariant::fromValue(item->color());
        break;
    case Percent:
        var= QVariant::fromValue(static_cast<qreal>(item->speakingTime() / m_maxSpeakingTime));
        break;
    case Hidden:
        var= QVariant::fromValue(item->hidden());
        break;
    case Position:
        var= QVariant::fromValue(item->position());
        break;
    default:
        break;
    }
    return var;
}

bool CharacterAvatarModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if(!index.isValid())
        return false;

    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(value.toString().isEmpty())
            return false;
        QVector<int> roles;
        auto item= m_persons[index.row()];
        roles << role;

        switch(index.column())
        {
        case 0:
            item->setName(value.toString());
            roles << Name;
            break;
        case 1:
            item->setPlayerName(value.toString());
            roles << PlayerName;
            break;
        case 2:
            item->setImgId(value.toString());
            roles << ImageId;
            break;
        case 3:
            item->setCampaign(value.toString());
            roles << Campaign;
            break;
        case 4:
            item->setColor(value.value<QColor>());
            roles << Color;
            break;
        }
        emit dataChanged(index, index, roles);
        return true;
    }
    if(role == Hidden)
    {
        auto item= m_persons[index.row()];
        if(item)
        {
            item->setHidden(value.toBool());
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
    }
    if(role == Position)
    {
        auto item= m_persons[index.row()];
        if(item)
        {
            item->setPosition(value.toPointF());
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }
    }

    return false;
}

Qt::ItemFlags CharacterAvatarModel::flags(const QModelIndex& index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

int CharacterAvatarModel::rowCount(const QModelIndex& parent) const
{
    return m_persons.size();
}

int CharacterAvatarModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QHash<int, QByteArray> CharacterAvatarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Name, "name");
    roles.insert(PlayerName, "player");
    roles.insert(ImageId, "img");
    roles.insert(Campaign, "campaign");
    roles.insert(IsSpeaking, "isSpeaking");
    roles.insert(SpeakingTime, "speakingTime");
    roles.insert(Percent, "percent");
    roles.insert(Color, "colorCh");
    roles.insert(Position, "position");
    roles.insert(GameMaster, "gameMaster");
    return roles;
}

QModelIndex CharacterAvatarModel::index(int row, int column, const QModelIndex& parent) const
{
    if(column < 0 || column >= 5 || row < 0 || row >= m_persons.size())
        return {};

    return createIndex(row, column);
}

void CharacterAvatarModel::resetData(std::vector<Character*> person)
{
    beginResetModel();
    m_persons.clear();
    m_persons= person;
    endResetModel();
}

void CharacterAvatarModel::addPerson(Character* person)
{
    beginInsertRows(QModelIndex(), m_persons.size(), m_persons.size());
    m_persons.push_back(person);
    endInsertRows();
}

QModelIndex CharacterAvatarModel::parent(const QModelIndex& child) const
{
    return {};
}

void CharacterAvatarModel::speakingStatusChanged(QString user, bool isSpeaking)
{
    int i= 0;
    for(auto character : m_persons)
    {
        if(character->playerName() == user)
        {
            qDebug() << "find Player";
            character->setIsSpeaking(isSpeaking);
            auto idx= createIndex(i, 0);
            dataChanged(idx, idx, QVector<int>() << IsSpeaking);
        }
        ++i;
    }
}

void CharacterAvatarModel::setSpeakingTimeForUser(QString user, QString camp, qreal time)
{
    auto it= std::find_if(m_persons.begin(), m_persons.end(),
                          [=](const Character* a) { return (a->playerName() == user && a->campaign() == camp); });
    if(it == m_persons.end())
        return;
    if(m_maxSpeakingTime < time)
    {
        m_maxSpeakingTime= time;
    }
    // int i = std::distance(m_persons.begin(),it);
    auto start= createIndex(0, 0);
    auto end= createIndex(m_persons.size(), 0);
    (*it)->setSpeakingTime(time);
    dataChanged(start, end, QVector<int>() << SpeakingTime << Percent);
}
QVariant CharacterAvatarModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if((role == Qt::DisplayRole) && (orientation == Qt::Horizontal))
    {
        QStringList list;
        list << "Nom"
             << "Nom Joueur"
             << "Image"
             << "Campagne"
             << "Couleur";
        return list[section];
    }
    else
    {
        return QVariant();
    }
}

const std::vector<Character*>& CharacterAvatarModel::characters() const
{
    return m_persons;
}

qreal CharacterAvatarModel::maxSpeakingTime() const
{
    return m_maxSpeakingTime;
}

void CharacterAvatarModel::setMaxSpeakingTime(const qreal& maxSpeakingTime)
{
    if(qFuzzyCompare(m_maxSpeakingTime, maxSpeakingTime))
        return;

    m_maxSpeakingTime= maxSpeakingTime;
    emit totaltimeChanged();
}

Character* CharacterAvatarModel::characterAt(int i) const
{
    if(m_persons.size() <= i || m_persons.empty())
        return nullptr;

    return m_persons.at(i);
}

void CharacterAvatarModel::writeData(QJsonArray& array)
{
    for(auto character : m_persons)
    {
        QJsonObject object;
        object["name"]= character->name();
        object["playername"]= character->playerName();
        object["imageId"]= character->imgId();
        object["color"]= character->color().name();
        object["campaign"]= character->campaign();
        object["id"]= character->id();
        object["x"]= character->position().x();
        object["y"]= character->position().y();
        object["gm"]= character->gamemaster();
        array.append(object);
    }
}
void CharacterAvatarModel::readData(QJsonArray& array)
{
    beginResetModel();
    qDeleteAll(std::begin(m_persons), std::end(m_persons));
    m_persons.clear();
    for(auto item : array)
    {
        auto obj= item.toObject();
        auto name= obj["name"].toString();
        auto playerName= obj["playername"].toString();
        auto imageId= obj["imageId"].toString();
        auto color= obj["color"].toString();
        auto campaign= obj["campaign"].toString();
        auto id= obj["id"].toString();
        auto x= obj["x"].toDouble();
        auto y= obj["y"].toDouble();
        auto gm= obj["gm"].toBool();
        auto character= new Character(name, playerName, imageId, campaign, QColor(color), id, gm);
        character->setPosition({x, y});
        m_persons.push_back(character);
    }
    endResetModel();
}
