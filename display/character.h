#ifndef CHARACTER_H
#define CHARACTER_H


#include <QString>

class Character
{
public:
    Character(QString, QString, QString,QString);

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

private:
    QString m_name;
    QString m_playerName;
    bool m_isSpeaking;
    QString m_imgId;
    QString m_campaign;
};

#endif // CHARACTER_H
