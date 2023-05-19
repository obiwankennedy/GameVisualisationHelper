QT       += core gui dbus quick qml svg webenginequick xml quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


include(third/qmarkdowntextedit/qmarkdowntextedit.pri)

CONFIG += c++11

TEMPLATE = app
TARGET = display
RESOURCES += resources.qrc

OTHER_FILES += qml/*.qml

SOURCES += main.cpp\
  centeredcheckbox.cpp \
  checkboxdelegate.cpp \
  clandelegate.cpp \
  controller/charactercontroller.cpp \
  controller/previewcontroller.cpp \
  diaporamamodel.cpp \
  guiadaptor.cpp \
  maincontroller.cpp \
  mainwindow.cpp \
  characteravatarmodel.cpp \
  model/calendaritemmodel.cpp \
  model/charactermodel.cpp \
  model/haikumodel.cpp \
  model/sortedmodel.cpp \
  model/sortfiltermodel.cpp \
  player.cpp \
  presentproxymodel.cpp \
  utils/iohelper.cpp \
  widgets/dragabletableview.cpp \
  widgets/l5rcharactersheetdialog.cpp

HEADERS  += mainwindow.h \
  centeredcheckbox.h \
  checkboxdelegate.h \
  clandelegate.h \
  controller/charactercontroller.h \
  controller/previewcontroller.h \
  coretype.h \
  diaporamamodel.h \
  guiadaptor.h \
  characteravatarmodel.h \
  maincontroller.h \
  model/calendaritemmodel.h \
  model/charactermodel.h \
  model/haikumodel.h \
  model/sortedmodel.h \
  model/sortfiltermodel.h \
  player.h \
  presentproxymodel.h \
  utils/iohelper.h \
  widgets/dragabletableview.h \
  widgets/l5rcharactersheetdialog.h

FORMS    += mainwindow.ui \
  widgets/l5rcharactersheetdialog.ui

DISTFILES += \
    CMakeLists.txt \
    qml/Effect01/export/qmldir \
    qml/MapViewerGenerique.qml \
    qml/SheetViewer.qml \
    qml/bbb.qmodel \
    resources/oneshotFreaks/out/Hikaru_Ichijo.jpg \
    resources/oneshotFreaks/out/Hikaru_Ichijo-gray.jpg \
    resources/oneshotFreaks/out/Lilly_Claudel.jpg \
    resources/oneshotFreaks/out/Lilly_Claudel-gray.jpg \
    resources/oneshotFreaks/out/MJ_.jpg \
    resources/oneshotFreaks/out/MJ_-gray.jpg \
    resources/oneshotFreaks/out/Renan_Charbonnier.jpg \
    resources/oneshotFreaks/out/Renan_Charbonnier-gray.jpg

STATECHARTS += \
  qml/aa.scxml


