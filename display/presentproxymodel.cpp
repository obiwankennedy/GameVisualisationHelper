#include "presentproxymodel.h"
#include "characteravatarmodel.h"

#include <QModelIndex>

PresentProxyModel::PresentProxyModel()
{

}

bool PresentProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    auto it = std::found(m_present.begin(),m_present.end(),source_parent.data(CharacterAvatarModel::PlayerName));

    return it != m_present.end();
}

std::vector<QString> PresentProxyModel::present() const
{
    return m_present;
}

void PresentProxyModel::setPresent(const std::vector<QString> &present)
{
    m_present = present;
}
