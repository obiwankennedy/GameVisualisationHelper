#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T16:08:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = teamspeakPlugin
TEMPLATE = subdirs
SUBDIRS =  plugin display


OTHER_FILES = plugin/plugin.pro display/display.pro








INSTALLS += target

RESOURCES += \
    resources.qrc
