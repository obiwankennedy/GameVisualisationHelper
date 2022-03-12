QT       += core gui dbus quick qml svg webenginequick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = app
TARGET = display
RESOURCES += resources.qrc

OTHER_FILES += qml/*.qml

SOURCES += main.cpp\
  controller/charactercontroller.cpp \
  diaporamamodel.cpp \
        guiadaptor.cpp \
  maincontroller.cpp \
        mainwindow.cpp \
    characteravatarmodel.cpp \
  model/charactermodel.cpp \
  player.cpp \
    presentproxymodel.cpp \
  utils/iohelper.cpp

HEADERS  += mainwindow.h \
  controller/charactercontroller.h \
  coretype.h \
  diaporamamodel.h \
        guiadaptor.h \
    characteravatarmodel.h \
  maincontroller.h \
  model/charactermodel.h \
  player.h \
    presentproxymodel.h \
  utils/iohelper.h

FORMS    += mainwindow.ui

DISTFILES += \
    qml/SheetViewer.qml \
    resources/oneshotFreaks/out/Hikaru_Ichijo.jpg \
    resources/oneshotFreaks/out/Hikaru_Ichijo-gray.jpg \
    resources/oneshotFreaks/out/Lilly_Claudel.jpg \
    resources/oneshotFreaks/out/Lilly_Claudel-gray.jpg \
    resources/oneshotFreaks/out/MJ_.jpg \
    resources/oneshotFreaks/out/MJ_-gray.jpg \
    resources/oneshotFreaks/out/Renan_Charbonnier.jpg \
    resources/oneshotFreaks/out/Renan_Charbonnier-gray.jpg


