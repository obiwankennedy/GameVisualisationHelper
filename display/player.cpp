#include "player.h"

Player::Player(QString name, QString player, QString img, QString cmp, QColor color, QString id, bool gamemaster)
    : m_name(name)
    , m_playerName(player)
    , m_imgId(img)
    , m_campaign(cmp)
    , m_color(color)
    , m_id(id)
    , m_gamemaster(gamemaster)
{
}

QString Player::name() const
{
    return m_name;
}

void Player::setName(const QString& name)
{
    if(name == m_name)
        return;
    m_name= name;
    emit nameChanged();
}

QString Player::playerName() const
{
    return m_playerName;
}

void Player::setPlayerName(const QString& playerName)
{
    if(playerName == m_playerName)
        return;

    m_playerName= playerName;
    emit playerNameChanged();
}

bool Player::isSpeaking() const
{
    return m_isSpeaking;
}
void Player::setIsSpeaking(bool isSpeaking)
{
    if(isSpeaking == m_isSpeaking)
        return;
    m_isSpeaking= isSpeaking;

    emit isSpeakingChanged();
}

QString Player::imgId() const
{
    return m_imgId;
}

void Player::setImgId(const QString& imgId)
{
    if(imgId == m_imgId)
        return;
    m_imgId= imgId;
    emit imgIdChanged();
}

QString Player::campaign() const
{
    return m_campaign;
}

void Player::setCampaign(const QString& campaign)
{
    m_campaign= campaign;
}

quint64 Player::speakingTime() const
{
    return m_speakingTime;
}

void Player::setSpeakingTime(const quint64& speakingTime)
{
    if(speakingTime == m_speakingTime)
        return;
    m_speakingTime= speakingTime;
    emit speakingTimeChanged();
}

QColor Player::color() const
{
    return m_color;
}

void Player::setColor(const QColor& color)
{
    if(color == m_color)
        return;
    m_color= color;
    emit colorChanged();

}

bool Player::hidden() const
{
    return m_hidden;
}

void Player::setHidden(bool v)
{
    if(m_hidden == v)
        return;
    m_hidden= v;
    emit hiddenChanged();
}

QString Player::id() const
{
    return m_id;
}

QPointF Player::position() const
{
    return m_position;
}

void Player::setPosition(QPointF newPosition)
{
    if(m_position == newPosition)
        return;
    m_position= newPosition;
    emit positionChanged();
}

bool Player::gamemaster() const
{
    return m_gamemaster;
}

const QString &Player::sheet() const
{
    return m_sheet;
}

void Player::setSheet(const QString &newSheet)
{
    if (m_sheet == newSheet)
        return;
    m_sheet = newSheet;
    emit sheetChanged();
}

QPointF Player::positionBis() const
{
    return m_positionBis;
}

void Player::setPositionBis(QPointF newPositionBis)
{
    if (m_positionBis == newPositionBis)
        return;
    m_positionBis = newPositionBis;
    emit positionBisChanged();
}
