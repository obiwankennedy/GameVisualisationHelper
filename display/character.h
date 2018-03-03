#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QColor>

class Character
{
public:
    Character(QString, QString, QString,QString, QColor);

    QString name() const;
    void setName(const QString &name);

    QString playerName() const;
    void setPlayerName(const QString &playerName);

    bool isSpeaking() const;
    void setIsSpeaking(bool isSpeaking);

    QString imgId() const;
    void setImgId(const QString &imgId);

    QString campaign() const;
    void setCampaign(const QString &campaign);

    quint64 speakingTime() const;
    void setSpeakingTime(const quint64 &speakingTime);

    QColor color() const;
    void setColor(const QColor &color);

private:
    QString m_name;
    QString m_playerName;
    bool m_isSpeaking = false;
    QString m_imgId;
    QString m_campaign;
    QColor m_color;
    quint64 m_speakingTime = 0;
};

#endif // CHARACTER_H
