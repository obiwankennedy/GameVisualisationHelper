TARGET = teamspeakPlugin
TEMPLATE = lib
INCLUDEPATH = /home/renaud/application/other/pluginsdk/include/

SOURCES += plugin.cpp
HEADERS += plugin.h
target.path = /opt/apps/TeamSpeak3-Client-linux_amd64/plugins/

INSTALLS += target
