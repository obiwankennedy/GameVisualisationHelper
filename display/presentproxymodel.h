#ifndef PRESENTPROXYMODEL_H
#define PRESENTPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QStringList>

class SelectPresentProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    SelectPresentProxyModel();


    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QString currentCampaign() const;
    void setCurrentCampaign(const QString &currentCampaign);

    QStringList list() const;
    void setList(const QStringList &list);
    Qt::ItemFlags flags(const QModelIndex &index) const;
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
signals:
    void selectionChanged();

private:
    QString m_currentCampaign;
    QStringList m_list;
};



class PresentProxyModel : public QSortFilterProxyModel
{
public:
    PresentProxyModel();


    QStringList hiddenPeople() const;
    void setHiddenPeople(const QStringList &hiddenPeople);

    QString currentCampaign() const;
    void setCurrentCampaign(const QString &currentCampaign);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
private:
    QStringList m_hiddenPeople;
    QString m_currentCampaign;
};

#endif // PRESENTPROXYMODEL_H
