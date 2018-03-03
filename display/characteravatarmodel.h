#ifndef CHARACTERAVATARMODEL_H
#define CHARACTERAVATARMODEL_H

#include <QAbstractListModel>
#include <QMap>
class Character;

class CharacterAvatarModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Role {Name = Qt::UserRole+1,
              PlayerName,
              ImageId,
              IsSpeaking,
              Campaign,
              SpeakingTime,
              Color};

    CharacterAvatarModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent) const;
    QHash<int, QByteArray> roleNames() const;

    void resetData(std::vector<Character*> person);

    void addPerson(Character* person);


    void speakingStatusChanged(QString user, bool isSpeaking);



private:
    std::vector<Character*> m_persons;
};

#endif // CHARACTERAVATARMODEL_H
