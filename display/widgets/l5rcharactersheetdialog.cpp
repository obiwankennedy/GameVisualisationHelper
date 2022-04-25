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
#include "l5rcharactersheetdialog.h"
#include "ui_l5rcharactersheetdialog.h"

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
L5RCharacterSheetDialog::L5RCharacterSheetDialog(const QHash<QString, QString>& newSheetProperties, QWidget* parent)
    : QDialog(parent), ui(new Ui::L5RCharacterSheetDialog), m_sheetProperties(newSheetProperties)
{
    ui->setupUi(this);

    // Make sure all values are in the hash
    m_sheetProperties.value(keys::key_name);
    m_sheetProperties.value(keys::key_school);
    m_sheetProperties.value(keys::key_clan);
    m_sheetProperties.value(keys::key_glory);
    m_sheetProperties.value(keys::key_honor);
    m_sheetProperties.value(keys::key_teint);
    m_sheetProperties.value(keys::key_pv);
    m_sheetProperties.value(keys::key_status);
    m_sheetProperties.value(keys::key_rank1t);
    m_sheetProperties.value(keys::key_rank1d);
    m_sheetProperties.value(keys::key_rank2t);
    m_sheetProperties.value(keys::key_rank2d);
    m_sheetProperties.value(keys::key_rank3t);
    m_sheetProperties.value(keys::key_rank3d);
    m_sheetProperties.value(keys::key_rank4t);
    m_sheetProperties.value(keys::key_rank4d);
    m_sheetProperties.value(keys::key_rank5t);
    m_sheetProperties.value(keys::key_rank5d);
    m_sheetProperties.value(keys::key_ranka1t);
    m_sheetProperties.value(keys::key_ranka1d);
    m_sheetProperties.value(keys::key_ranka2t);
    m_sheetProperties.value(keys::key_ranka2d);
    m_sheetProperties.value(keys::key_ranka3t);
    m_sheetProperties.value(keys::key_ranka3d);
    m_sheetProperties.value(keys::key_volonte);
    m_sheetProperties.value(keys::key_constitu);
    m_sheetProperties.value(keys::key_reflexe);
    m_sheetProperties.value(keys::key_intuition);
    m_sheetProperties.value(keys::key_agility);
    m_sheetProperties.value(keys::key_intelli);
    m_sheetProperties.value(keys::key_force);
    m_sheetProperties.value(keys::key_perception);
    m_sheetProperties.value(keys::key_void);
    m_sheetProperties.value(keys::key_skills);
    m_sheetProperties.value(keys::key_advs);
    m_sheetProperties.value(keys::key_defaut);

    updateUi();
}

L5RCharacterSheetDialog::~L5RCharacterSheetDialog()
{
    delete ui;
}

void L5RCharacterSheetDialog::changeEvent(QEvent* e)
{
    QDialog::changeEvent(e);
    switch(e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QHash<QString, QString> L5RCharacterSheetDialog::sheetProperties() const
{
    QHash<QString, QString> res;
    res[keys::key_name]= ui->m_name->text();
    res[keys::key_school]= ui->m_school->text();
    res[keys::key_clan]= ui->m_clan->text();
    res[keys::key_glory]= ui->m_gloire->text();
    res[keys::key_honor]= ui->m_honor->text();
    res[keys::key_teint]= ui->m_souillure->text();
    res[keys::key_pv]= ui->m_pv->text();
    res[keys::key_rank1t]= ui->m_rang1t->text();
    res[keys::key_rank1d]= ui->m_rang1d->toPlainText();
    res[keys::key_rank2t]= ui->m_rang2t->text();
    res[keys::key_rank2d]= ui->m_rang2d->toPlainText();
    res[keys::key_rank3t]= ui->m_rang3t->text();
    res[keys::key_rank3d]= ui->m_rang3d->toPlainText();
    res[keys::key_rank4t]= ui->m_rang4t->text();
    res[keys::key_rank4d]= ui->m_rang4d->toPlainText();
    res[keys::key_rank5t]= ui->m_rang5t->text();
    res[keys::key_rank5d]= ui->m_rang5d->toPlainText();
    res[keys::key_ranka1t]= ui->m_ranga1t->text();
    res[keys::key_ranka1d]= ui->m_ranga1d->toPlainText();
    res[keys::key_ranka2t]= ui->m_ranga2t->text();
    res[keys::key_ranka2d]= ui->m_ranga2d->toPlainText();
    res[keys::key_ranka3t]= ui->m_ranga3t->text();
    res[keys::key_ranka3d]= ui->m_ranga3d->toPlainText();
    res[keys::key_volonte]= ui->m_volo->text();
    res[keys::key_constitu]= ui->m_const->text();
    res[keys::key_reflexe]= ui->m_reflexes->text();
    res[keys::key_intuition]= ui->m_intuition->text();
    res[keys::key_agility]= ui->m_agi->text();
    res[keys::key_intelli]= ui->m_intell->text();
    res[keys::key_force]= ui->m_force->text();
    res[keys::key_perception]= ui->m_percep->text();
    res[keys::key_void]= ui->m_vide->text();
    res[keys::key_skills]= ui->m_comps->toPlainText();
    res[keys::key_advs]= ui->m_adv->toPlainText();
    res[keys::key_defaut]= ui->m_defaut->toPlainText();
    res[keys::key_status]= ui->m_status->text();
    return res;
}

void L5RCharacterSheetDialog::updateUi()
{
    ui->m_name->setText(m_sheetProperties[keys::key_name]);
    ui->m_status->setText(m_sheetProperties[keys::key_status]);
    ui->m_school->setText(m_sheetProperties[keys::key_school]);
    ui->m_clan->setText(m_sheetProperties[keys::key_clan]);
    ui->m_gloire->setText(m_sheetProperties[keys::key_glory]);
    ui->m_honor->setText(m_sheetProperties[keys::key_honor]);
    ui->m_souillure->setText(m_sheetProperties[keys::key_teint]);
    ui->m_pv->setText(m_sheetProperties[keys::key_pv]);
    ui->m_rang1t->setText(m_sheetProperties[keys::key_rank1t]);
    ui->m_rang1d->setPlainText(m_sheetProperties[keys::key_rank1d]);
    ui->m_rang2t->setText(m_sheetProperties[keys::key_rank2t]);
    ui->m_rang2d->setPlainText(m_sheetProperties[keys::key_rank2d]);
    ui->m_rang3t->setText(m_sheetProperties[keys::key_rank3t]);
    ui->m_rang3d->setPlainText(m_sheetProperties[keys::key_rank3d]);
    ui->m_rang4t->setText(m_sheetProperties[keys::key_rank4t]);
    ui->m_rang4d->setPlainText(m_sheetProperties[keys::key_rank4d]);
    ui->m_rang5t->setText(m_sheetProperties[keys::key_rank5t]);
    ui->m_rang5d->setPlainText(m_sheetProperties[keys::key_rank5d]);
    ui->m_ranga1t->setText(m_sheetProperties[keys::key_ranka1t]);
    ui->m_ranga1d->setPlainText(m_sheetProperties[keys::key_ranka1d]);
    ui->m_ranga2t->setText(m_sheetProperties[keys::key_ranka2t]);
    ui->m_ranga2d->setPlainText(m_sheetProperties[keys::key_ranka2d]);
    ui->m_ranga3t->setText(m_sheetProperties[keys::key_ranka3t]);
    ui->m_ranga3d->setPlainText(m_sheetProperties[keys::key_ranka3d]);
    ui->m_volo->setText(m_sheetProperties[keys::key_volonte]);
    ui->m_const->setText(m_sheetProperties[keys::key_constitu]);
    ui->m_reflexes->setText(m_sheetProperties[keys::key_reflexe]);
    ui->m_intuition->setText(m_sheetProperties[keys::key_intuition]);
    ui->m_agi->setText(m_sheetProperties[keys::key_agility]);
    ui->m_intell->setText(m_sheetProperties[keys::key_intelli]);
    ui->m_force->setText(m_sheetProperties[keys::key_force]);
    ui->m_percep->setText(m_sheetProperties[keys::key_perception]);
    ui->m_vide->setText(m_sheetProperties[keys::key_void]);
    ui->m_comps->setPlainText(m_sheetProperties[keys::key_skills]);
    ui->m_adv->setPlainText(m_sheetProperties[keys::key_advs]);
    ui->m_defaut->setPlainText(m_sheetProperties[keys::key_defaut]);
}
