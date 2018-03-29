#include "characteravatarmodel.h"

#include "character.h"
#include <QDebug>

CharacterAvatarModel::CharacterAvatarModel(QObject* parent)
    : QAbstractItemModel(parent)
{

}

QVariant CharacterAvatarModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};

    QVariant var;
    auto item =  m_persons[index.row()];

    switch(role)
    {
    case Qt::DisplayRole:
        switch(index.column())
        {
        case 0:
            var = QVariant::fromValue(item->name());
        break;
        case 1:
            var = QVariant::fromValue(item->playerName());
        break;
        case 2:
            var = QVariant::fromValue(item->imgId());
        break;
        case 3:
            var = QVariant::fromValue(item->campaign());
        break;
        case 4:
            var = QVariant::fromValue(item->color());
        break;
        }
        break;
    case Name:
        var = QVariant::fromValue(item->name());
        break;
    case PlayerName:
        var = QVariant::fromValue(item->playerName());
        break;
    case ImageId:
        var = QVariant::fromValue(item->imgId());
        break;
    case IsSpeaking:
        var = QVariant::fromValue(item->isSpeaking());
        break;
    case Campaign:
        var = QVariant::fromValue(item->campaign());
        break;
    case SpeakingTime:
        var = QVariant::fromValue(item->speakingTime());
        break;
    case Color:
        var = QVariant::fromValue(item->color());
        break;
    case Percent:
        var =QVariant::fromValue(static_cast<qreal>(item->speakingTime()/m_maxSpeakingTime));
        break;
    default:
        break;
    }
    return var;
}

bool CharacterAvatarModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    if(role == Qt::DisplayRole|| role == Qt::EditRole)
    {
        auto item =  m_persons[index.row()];

        switch(index.column())
        {
        case 0:
            item->setName(value.toString());
        break;
        case 1:
            item->setPlayerName(value.toString());
        break;
        case 2:
            item->setImgId(value.toString());
        break;
        case 3:
            item->setCampaign(value.toString());
        break;
        case 4:
            item->setColor(value.value<QColor>());
        break;
        }
        return true;
    }
    return false;

}

Qt::ItemFlags CharacterAvatarModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

int CharacterAvatarModel::rowCount(const QModelIndex &parent) const
{
    return m_persons.size();
}

int CharacterAvatarModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QHash<int, QByteArray> CharacterAvatarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Name,"name");
    roles.insert(PlayerName,"player");
    roles.insert(ImageId,"img");
    roles.insert(Campaign,"campaign");
    roles.insert(IsSpeaking,"isSpeaking");
    roles.insert(SpeakingTime,"speakingTime");
    roles.insert(Percent,"percent");
    roles.insert(Color,"colorCh");
    return roles;
}

QModelIndex CharacterAvatarModel::index(int row, int column, const QModelIndex &parent) const
{
   if(column<0 || column >= 5 || row < 0 || row >= m_persons.size())
       return {};

   return createIndex(row,column);
}

void CharacterAvatarModel::resetData(std::vector<Character*> person)
{
    beginResetModel();
    m_persons.clear();
    m_persons = person;
    endResetModel();
}

void CharacterAvatarModel::addPerson(Character* person)
{
    beginInsertRows(QModelIndex(),m_persons.size(),m_persons.size());
    m_persons.push_back(person);
    endInsertRows();

}

QModelIndex CharacterAvatarModel::parent(const QModelIndex &child) const
{
    return {};
}

void CharacterAvatarModel::speakingStatusChanged(QString user, bool isSpeaking)
{
    int i = 0;
    for(auto character : m_persons)
    {
        if(character->playerName() == user)
        {
            character->setIsSpeaking(isSpeaking);
            auto idx = createIndex(i,0);
            dataChanged(idx,idx,QVector<int>() << IsSpeaking);
        }
        ++i;
    }
}

void CharacterAvatarModel::setSpeakingTimeForUser(QString user,QString camp, qreal time)
{
    if(m_maxSpeakingTime < time)
    {
        m_maxSpeakingTime = time;
    }
    auto it = std::find_if(m_persons.begin(),m_persons.end(),[=](const Character* a){
        return (a->playerName() == user && a->campaign() == camp);
    });
    if(it == m_persons.end())
        return;
    //int i = std::distance(m_persons.begin(),it);
    auto start = createIndex(0,0);
    auto end = createIndex(m_persons.size(),0);
    (*it)->setSpeakingTime(time);
    dataChanged(start,end,QVector<int>() << SpeakingTime << Percent);
}
QVariant CharacterAvatarModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if((role==Qt::DisplayRole)&&(orientation == Qt::Horizontal))
    {
        QStringList list;
        list << "Nom" << "Nom Joueur" << "Image" << "Campagne" << "Couleur";
        return list[section];
    }
    else
    {
        return QVariant();
    }
}
qreal CharacterAvatarModel::maxSpeakingTime() const
{
    return m_maxSpeakingTime;
}

void CharacterAvatarModel::setMaxSpeakingTime(const qreal &maxSpeakingTime)
{
    m_maxSpeakingTime = maxSpeakingTime;
}
