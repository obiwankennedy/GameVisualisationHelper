/***************************************************************************
 *	Copyright (C) 2022 by Renaud Guezennec                               *
 *   http://www.rolisteam.org/contact                                      *
 *                                                                         *
 *   This software is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef L5RCHARACTERSHEETDIALOG_H
#define L5RCHARACTERSHEETDIALOG_H

#include <QDialog>
#include <QHash>
#include <QString>

namespace Ui
{
class L5RCharacterSheetDialog;
}

namespace keys
{
// generals
constexpr char const* key_name{"name"};
constexpr char const* key_school{"school"};
constexpr char const* key_clan{"clan"};
constexpr char const* key_glory{"glory"};
constexpr char const* key_honor{"honor"};
constexpr char const* key_teint{"teint"};
constexpr char const* key_status{"status"};
constexpr char const* key_pv{"pv"};

// schools
constexpr char const* key_rank1t{"rank1t"};
constexpr char const* key_rank1d{"rank1d"};
constexpr char const* key_rank2t{"rank2t"};
constexpr char const* key_rank2d{"rank2d"};
constexpr char const* key_rank3t{"rank3t"};
constexpr char const* key_rank3d{"rank3d"};
constexpr char const* key_rank4t{"rank4t"};
constexpr char const* key_rank4d{"rank4d"};
constexpr char const* key_rank5t{"rank5t"};
constexpr char const* key_rank5d{"rank5d"};
constexpr char const* key_ranka1t{"ranka1t"};
constexpr char const* key_ranka1d{"ranka1d"};
constexpr char const* key_ranka2t{"ranka2t"};
constexpr char const* key_ranka2d{"ranka2d"};
constexpr char const* key_ranka3t{"ranka3t"};
constexpr char const* key_ranka3d{"ranka3d"};

// attributs:
// earth
constexpr char const* key_volonte{"volonte"};
constexpr char const* key_constitu{"constittue"};
// air
constexpr char const* key_reflexe{"reflexe"};
constexpr char const* key_intuition{"intuition"};
// fire
constexpr char const* key_agility{"agility"};
constexpr char const* key_intelli{"intelligence"};
// Water
constexpr char const* key_force{"force"};
constexpr char const* key_perception{"perception"};

constexpr char const* key_void{"void"};
// skill defaut adv
constexpr char const* key_skills{"skills"};
constexpr char const* key_advs{"adv"};
constexpr char const* key_defaut{"defaut"};
} // namespace keys

class L5RCharacterSheetDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QHash<QString, QString> sheetProperties READ sheetProperties NOTIFY sheetPropertiesChanged)

public:
    explicit L5RCharacterSheetDialog(const QHash<QString, QString>& newSheetProperties, QWidget* parent= nullptr);
    ~L5RCharacterSheetDialog();

    QHash<QString, QString> sheetProperties() const;

signals:
    void sheetPropertiesChanged();

private slots:
    void updateUi();
    void setUpAction();

protected:
    void changeEvent(QEvent* e);

private:
    Ui::L5RCharacterSheetDialog* ui;
    QHash<QString, QString> m_sheetProperties;
};

#endif // L5RCHARACTERSHEETDIALOG_H
