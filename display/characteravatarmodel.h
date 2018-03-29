#ifndef CHARACTERAVATARMODEL_H
#define CHARACTERAVATARMODEL_H

#include <QAbstractListModel>
#include <QMap>
class Character;

class CharacterAvatarModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Role {Name = Qt::UserRole+1,
              PlayerName,
              ImageId,
              IsSpeaking,
              Campaign,
              SpeakingTime,
              Percent,
              Color};

    CharacterAvatarModel(QObject* parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void resetData(std::vector<Character*> person);

    void addPerson(Character* person);


    void speakingStatusChanged(QString user, bool isSpeaking);
    void setSpeakingTimeForUser(QString user,QString camp, qreal time);



    qreal maxSpeakingTime() const;
    void setMaxSpeakingTime(const qreal &maxSpeakingTime);

private:
    std::vector<Character*> m_persons;
    qreal m_maxSpeakingTime = 1;
};

#endif // CHARACTERAVATARMODEL_H
