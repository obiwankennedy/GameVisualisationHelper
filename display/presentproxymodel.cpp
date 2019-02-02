#include "presentproxymodel.h"
#include "characteravatarmodel.h"

#include <QSettings>
#include <QModelIndex>


PresentProxyModel::PresentProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    readSettings();
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
    writeSettings();
}

QString PresentProxyModel::currentCampaign() const
{
    return m_currentCampaign;
}

void PresentProxyModel::setCurrentCampaign(const QString &currentCampaign)
{
    m_currentCampaign = currentCampaign;
    readSettings();
    invalidateFilter();
}


void PresentProxyModel::writeSettings() const
{
    QSettings setting("Rolisteam","display");

   setting.setValue(QStringLiteral("presentlist_%1").arg(m_currentCampaign),m_hiddenPeople);
}

void PresentProxyModel::readSettings()
{
   QSettings setting("Rolisteam","display");
   m_hiddenPeople = setting.value(QStringLiteral("presentlist_%1").arg(m_currentCampaign)).toStringList();
}


/////////////////
/// \brief SelectPresentProxyModel::SelectPresentProxyModel
///////////////////
SelectPresentProxyModel::SelectPresentProxyModel(QObject* parent)
: PresentProxyModel(parent)
{

}



QVariant SelectPresentProxyModel::data(const QModelIndex &index, int role) const
{
    if(Qt::CheckStateRole == role)
    {
        auto name = QSortFilterProxyModel::data(index, CharacterAvatarModel::Name).toString();
        if(m_hiddenPeople.contains(name))
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
             m_hiddenPeople.removeAll(name);
        }
        else
        {
            m_hiddenPeople.append(name);
        }
        writeSettings();
        emit selectionChanged();
        return true;
    }
    return QSortFilterProxyModel::setData(index,value,role);
}


Qt::ItemFlags SelectPresentProxyModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
}

bool SelectPresentProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    auto index = sourceModel()->index(source_row, 0, source_parent);
    auto right = index.data(CharacterAvatarModel::Campaign).toString() == m_currentCampaign;
    return right;
}
