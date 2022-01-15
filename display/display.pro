QT       += core gui dbus quick qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TEMPLATE = app
TARGET = display
RESOURCES += resources.qrc

OTHER_FILES += qml/*.qml

SOURCES += main.cpp\
  diaporamamodel.cpp \
        guiadaptor.cpp \
  maincontroller.cpp \
        mainwindow.cpp \
    characteravatarmodel.cpp \
    character.cpp \
    presentproxymodel.cpp

HEADERS  += mainwindow.h \
  diaporamamodel.h \
        guiadaptor.h \
    characteravatarmodel.h \
    character.h \
  maincontroller.h \
    presentproxymodel.h

FORMS    += mainwindow.ui

DISTFILES += \
    resources/oneshotFreaks/out/Hikaru_Ichijo.jpg \
    resources/oneshotFreaks/out/Hikaru_Ichijo-gray.jpg \
    resources/oneshotFreaks/out/Lilly_Claudel.jpg \
    resources/oneshotFreaks/out/Lilly_Claudel-gray.jpg \
    resources/oneshotFreaks/out/MJ_.jpg \
    resources/oneshotFreaks/out/MJ_-gray.jpg \
    resources/oneshotFreaks/out/Renan_Charbonnier.jpg \
    resources/oneshotFreaks/out/Renan_Charbonnier-gray.jpg


