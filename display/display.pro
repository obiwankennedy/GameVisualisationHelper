QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = display

SOURCES += main.cpp\
        guiadaptor.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
        guiadaptor.h \
    main.h

FORMS    += mainwindow.ui

RESOURCES += resources.qrc
