/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c GuiAdaptor -a guiadaptor.h:guiadaptor.cpp org.rolisteam.display
 *
 * qdbusxml2cpp is Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "guiadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class GuiAdaptor
 */

GuiAdaptor::GuiAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

GuiAdaptor::~GuiAdaptor()
{
    // destructor
}

void GuiAdaptor::displayCorrectImage(const QString &user)
{
    // handle method call local.qdbuscpp2xml.MainWindow.displayCorrectImage
    QMetaObject::invokeMethod(parent(), "displayCorrectImage", Q_ARG(QString, user));
}

void GuiAdaptor::hideImage(const QString &user)
{
    // handle method call local.qdbuscpp2xml.MainWindow.hideImage
    QMetaObject::invokeMethod(parent(), "hideImage", Q_ARG(QString, user));
}

void GuiAdaptor::setImageInLabel()
{
    // handle method call local.qdbuscpp2xml.MainWindow.setImageInLabel
    QMetaObject::invokeMethod(parent(), "setImageInLabel");
}

