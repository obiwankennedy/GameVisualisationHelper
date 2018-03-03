#ifndef PRESENTPROXYMODEL_H
#define PRESENTPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
class PresentProxyModel : public QSortFilterProxyModel
{
public:
    PresentProxyModel();

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

    std::vector<QString> present() const;
    void setPresent(const std::vector<QString> &present);

private:
    std::vector<QString> m_present;


};

#endif // PRESENTPROXYMODEL_H
