#ifndef CHARACTER_H
#define CHARACTER_H

#include <QColor>
#include <QObject>
#include <QPointF>
#include <QString>

class Character : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString playerName READ playerName WRITE setPlayerName NOTIFY playerNameChanged)
    Q_PROPERTY(bool isSpeaking READ isSpeaking WRITE setIsSpeaking NOTIFY isSpeakingChanged)
    Q_PROPERTY(QString imgId READ imgId WRITE setImgId NOTIFY imgIdChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString campaign READ campaign CONSTANT)
    Q_PROPERTY(quint64 speakingTime READ speakingTime WRITE setSpeakingTime NOTIFY speakingTimeChanged)
    Q_PROPERTY(bool hidden READ hidden WRITE setHidden NOTIFY hiddenChanged)
    Q_PROPERTY(QPointF position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(bool gamemaster READ gamemaster CONSTANT)
public:
    Character(QString, QString, QString, QString, QColor, QString id, bool gamemaster= false);

    QString name() const;
    void setName(const QString& name);

    QString playerName() const;
    void setPlayerName(const QString& playerName);

    bool isSpeaking() const;
    void setIsSpeaking(bool isSpeaking);

    QString imgId() const;
    void setImgId(const QString& imgId);

    QString campaign() const;
    void setCampaign(const QString& campaign);

    quint64 speakingTime() const;
    void setSpeakingTime(const quint64& speakingTime);

    QColor color() const;
    void setColor(const QColor& color);

    bool hidden() const;
    void setHidden(bool v);

    QString id() const;

    QPointF position() const;
    void setPosition(QPointF newPosition);

    bool gamemaster() const;

signals:
    void nameChanged();
    void playerNameChanged();
    void isSpeakingChanged();
    void imgIdChanged();
    void colorChanged();
    void speakingTimeChanged();
    void hiddenChanged();
    void positionChanged();

private:
    QString m_name;
    QString m_playerName;
    bool m_isSpeaking= false;
    QString m_imgId;
    QString m_campaign;
    QColor m_color;
    quint64 m_speakingTime= 0;
    QString m_id;
    bool m_hidden= false;
    QPointF m_position;
    bool m_gamemaster{false};
};

#endif // CHARACTER_H
