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
    auto item =  m_person[index.row()];
    switch(role)
    {
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
    default:
        break;
    }
    return var;
}

Qt::ItemFlags CharacterAvatarModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable;
}

int CharacterAvatarModel::rowCount(const QModelIndex &parent) const
{
    return m_person.size();
}

QHash<int, QByteArray> CharacterAvatarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Name,"name");
    roles.insert(PlayerName,"player");
    roles.insert(ImageId,"img");
    roles.insert(Campaign,"campaign");
    roles.insert(IsSpeaking,"isSpeaking");
}

void CharacterAvatarModel::resetData(std::vector<Character *> person)
{
    beginResetModel();
    m_person.clear();
    m_person = person;
    endResetModel();
}

void CharacterAvatarModel::addPerson(Character* person)
{
    beginInsertRows(QModelIndex(),m_person.size(),m_person.size());
    m_person.push_back(person);
    endInsertRows();

}
