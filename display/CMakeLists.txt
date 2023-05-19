cmake_minimum_required(VERSION 3.15)


project(display VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Gui DBus Quick Qml Widgets Svg WebEngineQuick Xml QuickWidgets QmlImportScanner ShaderTools REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(markdownSrc
third/qmarkdowntextedit/linenumberarea.h
third/qmarkdowntextedit//markdownhighlighter.h
third/qmarkdowntextedit//qmarkdowntextedit.h
third/qmarkdowntextedit//qownlanguagedata.h
third/qmarkdowntextedit//qplaintexteditsearchwidget.h
third/qmarkdowntextedit//qownlanguagedata.h
third/qmarkdowntextedit/markdownhighlighter.cpp
third/qmarkdowntextedit/qmarkdowntextedit.cpp
third/qmarkdowntextedit/qownlanguagedata.cpp
third/qmarkdowntextedit/qplaintexteditsearchwidget.cpp
third/qmarkdowntextedit/media.qrc
third/qmarkdowntextedit/qplaintexteditsearchwidget.ui
)

set(SOURCES
main.cpp
centeredcheckbox.cpp
checkboxdelegate.cpp
clandelegate.cpp
controller/charactercontroller.cpp
controller/previewcontroller.cpp
diaporamamodel.cpp
guiadaptor.cpp
maincontroller.cpp
mainwindow.cpp
characteravatarmodel.cpp
model/calendaritemmodel.cpp
model/charactermodel.cpp
model/haikumodel.cpp
model/sortedmodel.cpp
model/sortfiltermodel.cpp
player.cpp
presentproxymodel.cpp
utils/iohelper.cpp
widgets/dragabletableview.cpp
widgets/l5rcharactersheetdialog.cpp)

set(HEADERS
mainwindow.h
centeredcheckbox.h
checkboxdelegate.h
clandelegate.h
controller/charactercontroller.h
controller/previewcontroller.h
coretype.h
diaporamamodel.h
guiadaptor.h
characteravatarmodel.h
maincontroller.h
model/calendaritemmodel.h
model/charactermodel.h
model/haikumodel.h
model/sortedmodel.h
model/sortfiltermodel.h
player.h
presentproxymodel.h
utils/iohelper.h
widgets/dragabletableview.h
widgets/l5rcharactersheetdialog.h)

set(forms mainwindow.ui  widgets/l5rcharactersheetdialog.ui)

set(other
qml/MapViewerGenerique.qml
qml/SheetViewer.qml
qml/CharacterItem.qml
qml/MapViewer.qml
qml/CustomFrame.qml
qml/GridGallery.qml
qml/Months.qml
qml/CalendarItem.qml
qml/ImagePathView.qml
qml/Seasons.qml
qml/Calendrier.qml
qml/ImageView.qml
qml/SheetViewer.qml
qml/Celebrations.qml
qml/glow.frag
qml/glow.vert
qml/main.qml
qml/Token.qml
qml/CenterContent.qml
qml/MapViewerGenerique.qml
)


# grayscale.frag.qsb

# qml/grayscale.frag


add_executable(display ${SOURCES} ${HEADERS} ${forms} ${other} ${markdownSrc} resources.qrc)

qt6_add_resources(display "display")

qt6_add_shaders(display "display_shaders"
    PREFIX
        "/"
    FILES
        "qml/glow.frag"
        "qml/glow.vert"
        "qml/bluritem.frag"
        "qml/bluritem.vert"
        "qml/grayscale.frag"
)

target_link_libraries(display PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets Qt6::DBus Qt6::Quick Qt6::Svg Qt6::WebEngineQuick Qt6::QuickWidgets Qt6::Xml )
target_include_directories(display PUBLIC . controller)
