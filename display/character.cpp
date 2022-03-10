#include "character.h"

Character::Character(QString name, QString player, QString img, QString cmp, QColor color, QString id, bool gamemaster)
    : m_name(name)
    , m_playerName(player)
    , m_imgId(img)
    , m_campaign(cmp)
    , m_color(color)
    , m_id(id)
    , m_gamemaster(gamemaster)
{
}

QString Character::name() const
{
    return m_name;
}

void Character::setName(const QString& name)
{
    if(name == m_name)
        return;
    m_name= name;
    emit nameChanged();
}

QString Character::playerName() const
{
    return m_playerName;
}

void Character::setPlayerName(const QString& playerName)
{
    if(playerName == m_playerName)
        return;

    m_playerName= playerName;
    emit playerNameChanged();
}

bool Character::isSpeaking() const
{
    return m_isSpeaking;
}
void Character::setIsSpeaking(bool isSpeaking)
{
    if(isSpeaking == m_isSpeaking)
        return;
    m_isSpeaking= isSpeaking;

    emit isSpeakingChanged();
}

QString Character::imgId() const
{
    return m_imgId;
}

void Character::setImgId(const QString& imgId)
{
    if(imgId == m_imgId)
        return;
    m_imgId= imgId;
    emit imgIdChanged();
}

QString Character::campaign() const
{
    return m_campaign;
}

void Character::setCampaign(const QString& campaign)
{
    m_campaign= campaign;
}

quint64 Character::speakingTime() const
{
    return m_speakingTime;
}

void Character::setSpeakingTime(const quint64& speakingTime)
{
    if(speakingTime == m_speakingTime)
        return;
    m_speakingTime= speakingTime;
    emit speakingTimeChanged();
}

QColor Character::color() const
{
    return m_color;
}

void Character::setColor(const QColor& color)
{
    m_color= color;
}

bool Character::hidden() const
{
    return m_hidden;
}

void Character::setHidden(bool v)
{
    if(m_hidden == v)
        return;
    m_hidden= v;
    emit hiddenChanged();
}

QString Character::id() const
{
    return m_id;
}

QPointF Character::position() const
{
    return m_position;
}

void Character::setPosition(QPointF newPosition)
{
    if(m_position == newPosition)
        return;
    m_position= newPosition;
    emit positionChanged();
}

bool Character::gamemaster() const
{
    return m_gamemaster;
}
