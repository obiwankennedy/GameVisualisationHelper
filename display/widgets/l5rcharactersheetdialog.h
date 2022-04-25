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

protected:
    void changeEvent(QEvent* e);

private:
    Ui::L5RCharacterSheetDialog* ui;
    QHash<QString, QString> m_sheetProperties;
};

#endif // L5RCHARACTERSHEETDIALOG_H
