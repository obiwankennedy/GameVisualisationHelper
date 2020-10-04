#ifndef PRESENTPROXYMODEL_H
#define PRESENTPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QStringList>

class PresentProxyModel : public QSortFilterProxyModel
{
public:
    explicit PresentProxyModel(QObject* parent= nullptr);

    /*QStringList hiddenPeople() const;
    void setHiddenPeople(const QStringList& hiddenPeople);*/

    QString currentCampaign() const;
    void setCurrentCampaign(const QString& currentCampaign);

    void writeSettings() const;
    void readSettings();

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;

protected:
    // QStringList m_hiddenPeople;
    QString m_currentCampaign;
};

class SelectPresentProxyModel : public PresentProxyModel
{
    Q_OBJECT
public:
    explicit SelectPresentProxyModel(QObject* parent= nullptr);

    QVariant data(const QModelIndex& index, int role) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role);

    Qt::ItemFlags flags(const QModelIndex& index) const;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
signals:
    void selectionChanged();
};

#endif // PRESENTPROXYMODEL_H
