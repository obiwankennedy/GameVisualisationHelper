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
#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QLabel>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickWindow>
#include <QScrollArea>

class PreviewController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentMode READ currentMode WRITE setCurrentMode NOTIFY currentModeChanged)
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(qreal imageWidth READ imageWidth NOTIFY imageWidthChanged)
    Q_PROPERTY(qreal imageHeight READ imageHeight NOTIFY imageHeightChanged)

public:
    explicit PreviewController(QObject* parent= nullptr);
    ~PreviewController();

    void setLabel(QLabel* label);

    int currentMode() const;
    void setCurrentMode(int newCurrentMode);

    const QImage& image() const;
    void setImage(const QImage& newImage);

    qreal imageWidth() const;
    qreal imageHeight() const;

signals:
    void currentModeChanged();
    void imageChanged();
    void imageWidthChanged();
    void imageHeightChanged();
    void sendEvent(QMouseEvent* event);

protected:
    void updateGeometry();
    bool eventFilter(QObject*, QEvent*);
    void setSize(qreal w, qreal h);

private:
    QPointer<QLabel> m_label;
    QScrollArea* m_widget;
    int m_currentMode;
    qreal m_imageW;
    qreal m_imageH;
    QImage m_image;
    qreal m_imageWidth;
    qreal m_imageHeight;
};
#endif
