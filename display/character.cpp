#include "character.h"

Character::Character(QString name, QString player, QString img,QString  cmp)
    : m_name(name), m_playerName(player), m_imgId(img), m_campaign(cmp)
{

}

QString Character::name() const
{
    return m_name;
}

void Character::setName(const QString &name)
{
    m_name = name;
}

QString Character::playerName() const
{
    return m_playerName;
}

void Character::setPlayerName(const QString &playerName)
{
    m_playerName = playerName;
}

bool Character::isSpeaking() const
{
    return m_isSpeaking;
}

void Character::setIsSpeaking(bool isSpeaking)
{
    m_isSpeaking = isSpeaking;
}

QString Character::imgId() const
{
    return m_imgId;
}

void Character::setImgId(const QString &imgId)
{
    m_imgId = imgId;
}

QString Character::campaign() const
{
    return m_campaign;
}

void Character::setCampaign(const QString &campaign)
{
    m_campaign = campaign;
}
