#include "characteravatarmodel.h"

#include "character.h"

CharacterAvatarModel::CharacterAvatarModel()
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
    default:
        break;
    }
    return var;
}

Qt::ItemFlags CharacterAvatarModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

int CharacterAvatarModel::rowCount(const QModelIndex &parent) const
{
    return m_persons.size();
}

QHash<int, QByteArray> CharacterAvatarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Name,"name");
    roles.insert(PlayerName,"player");
    roles.insert(ImageId,"img");
    roles.insert(Campaign,"campaign");
    roles.insert(IsSpeaking,"isSpeaking");
    roles.insert(SpeakingTime,"SpeakingTime");
    roles.insert(Color,"colorCh");

    return roles;
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
