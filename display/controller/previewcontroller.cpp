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
#include "previewcontroller.h"
#include <QMouseEvent>

PreviewController::PreviewController(QObject* parent) : QObject(parent)
{
    // m_engine= new QQmlApplicationEngine();

    /*m_timer= new QTimer();
    m_timer->setInterval(200);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(refreshView()));*/

    // m_engine->load(QUrl("qrc:/resources/qml/listView.qml"));

    // setResizeMode(QQuickView::SizeRootObjectToView);
}

PreviewController::~PreviewController() {}

void PreviewController::setLabel(QLabel* label)
{
    m_label= label;
    /*    m_ui= parent;
        m_label= new QLabel();
        m_label->setLineWidth(0);
        m_label->setFrameStyle(QFrame::NoFrame);
        m_ui->m_scrollAreaVisual->setWidget(m_label);
        m_ui->m_scrollAreaVisual->setAlignment(Qt::AlignCenter);
        m_ui->m_scrollAreaVisual->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_ui->m_scrollAreaVisual->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        m_label->setScaledContents(true);
        m_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        m_widget= m_ui->m_scrollAreaVisual;
        m_label->installEventFilter(this);*/
}

void PreviewController::updateGeometry()
{
    auto ratioImage= static_cast<double>(m_image.size().width()) / static_cast<double>(m_image.size().height());
    auto ratioImageBis= static_cast<double>(m_image.size().height()) / static_cast<double>(m_image.size().width());

    int w= m_widget->viewport()->rect().width();
    int h= m_widget->viewport()->rect().height();

    if(w > h * ratioImage)
    {
        setSize(static_cast<int>(h * ratioImage), h);
    }
    else
    {
        setSize(w, static_cast<int>(w * ratioImageBis));
    }
}

void PreviewController::setSize(qreal w, qreal h)
{
    if(!qFuzzyCompare(w, m_imageW))
    {
        m_imageW= w;
        emit imageWidthChanged();
    }

    if(!qFuzzyCompare(h, m_imageH))
    {
        m_imageH= h;
        emit imageHeightChanged();
    }
}

bool PreviewController::eventFilter(QObject* label, QEvent* vt)
{
    if(!m_label || m_label != label)
        return false;

    if((vt->type() == QEvent::MouseButtonPress) || (vt->type() == QEvent::MouseButtonRelease)
       || (vt->type() == QEvent::MouseMove))
    {
        QMouseEvent* evt= static_cast<QMouseEvent*>(vt);
        QPoint posOnLabel= evt->pos();

        int w= m_label->geometry().width();
        int h= m_label->geometry().height();

        qreal ratioW= static_cast<qreal>(1920) / static_cast<qreal>(w);
        qreal ratioH= static_cast<qreal>(1080) / static_cast<qreal>(h);

        qreal x= (posOnLabel.x()) * ratioW;
        qreal y= (posOnLabel.y()) * ratioH;

        QPointF posOnQML(x, y);
        QMouseEvent* event
            = new QMouseEvent(evt->type(), posOnQML.toPoint(), evt->button(), evt->buttons(), evt->modifiers());

        emit sendEvent(event);
        // QObject* root= m_engine->rootObjects().at(0);
        // QCoreApplication::sendEvent(m_window,event);
        // QCoreApplication::sendEvent(root, event);
        // m_window->sendEvent(m_window->contentItem(),event);
        return true;
    }
    return false;
}

int PreviewController::currentMode() const
{
    return m_currentMode;
}

void PreviewController::setCurrentMode(int newCurrentMode)
{
    if(m_currentMode == newCurrentMode)
        return;
    m_currentMode= newCurrentMode;
    emit currentModeChanged();
}

const QImage& PreviewController::image() const
{
    return m_image;
}

void PreviewController::setImage(const QImage& newImage)
{
    if(m_image == newImage)
        return;
    m_image= newImage;
    emit imageChanged();
}

qreal PreviewController::imageWidth() const
{
    return m_imageWidth;
}

qreal PreviewController::imageHeight() const
{
    return m_imageHeight;
}
