#include "character.h"

Character::Character(QString name, QString player, QString img,QString  cmp, QColor color)
    : m_name(name), m_playerName(player), m_imgId(img), m_campaign(cmp), m_color(color)
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

quint64 Character::speakingTime() const
{
    return m_speakingTime;
}

void Character::setSpeakingTime(const quint64 &speakingTime)
{
    m_speakingTime = speakingTime;
}

QColor Character::color() const
{
    return m_color;
}

void Character::setColor(const QColor &color)
{
    m_color = color;
}
