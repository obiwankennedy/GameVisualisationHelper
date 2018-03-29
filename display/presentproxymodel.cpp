#include "presentproxymodel.h"
#include "characteravatarmodel.h"

#include <QModelIndex>


PresentProxyModel::PresentProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{

}

bool PresentProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    auto index = sourceModel()->index(source_row, 0, source_parent);
    auto right = index.data(CharacterAvatarModel::Campaign).toString() == m_currentCampaign;
    return (!m_hiddenPeople.contains(index.data(CharacterAvatarModel::Name).toString()) & right);
}

QStringList PresentProxyModel::hiddenPeople() const
{
    return m_hiddenPeople;
}

void PresentProxyModel::setHiddenPeople(const QStringList &present)
{
    m_hiddenPeople = present;
    invalidateFilter();
}

QString PresentProxyModel::currentCampaign() const
{
    return m_currentCampaign;
}

void PresentProxyModel::setCurrentCampaign(const QString &currentCampaign)
{
    m_currentCampaign = currentCampaign;
    invalidateFilter();
}
/////////////////
/// \brief SelectPresentProxyModel::SelectPresentProxyModel
///////////////////
SelectPresentProxyModel::SelectPresentProxyModel(QObject* parent)
: QSortFilterProxyModel(parent)
{

}



QVariant SelectPresentProxyModel::data(const QModelIndex &index, int role) const
{
    if(Qt::CheckStateRole == role)
    {
        auto name = QSortFilterProxyModel::data(index, CharacterAvatarModel::Name).toString();
        if(m_list.contains(name))
        {
            return Qt::Checked;
        }
        else
        {
            return Qt::Unchecked;
        }
    }
    else
        return QSortFilterProxyModel::data(index,role);
}

bool SelectPresentProxyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(Qt::CheckStateRole == role)
    {
        auto name = QSortFilterProxyModel::data(index, CharacterAvatarModel::Name).toString();
        if(value.value<Qt::CheckState>() == Qt::Unchecked)
        {
             m_list.removeAll(name);
        }
        else
        {
            m_list.append(name);
        }
        emit selectionChanged();
        return true;
    }
    return QSortFilterProxyModel::setData(index,value,role);
}

QString SelectPresentProxyModel::currentCampaign() const
{
    return m_currentCampaign;
}

Qt::ItemFlags SelectPresentProxyModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
}

void SelectPresentProxyModel::setCurrentCampaign(const QString &currentCampaign)
{
    m_currentCampaign = currentCampaign;
    invalidateFilter();
}

QStringList SelectPresentProxyModel::list() const
{
    return m_list;
}

void SelectPresentProxyModel::setList(const QStringList &list)
{
    m_list = list;
}

bool SelectPresentProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    auto index = sourceModel()->index(source_row, 0, source_parent);
    auto right = index.data(CharacterAvatarModel::Campaign).toString() == m_currentCampaign;
    return right;
}
