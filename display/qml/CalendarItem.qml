import QtQuick 2.0
import QtQuick.Controls

MouseArea {
    id: _area
    property bool lock: false
    property int row: 0
    property string title:""
    property string desc:""
    property color color
    property real totalWidth
    property real itemHeight
    property real minimunWidth: isRound ? _area.itemHeight : 0
    property bool isRound: false
    property alias source: _img.source


    ToolTip.visible: pressed
    drag.target: _area.lock ? undefined : _area
    drag.axis: Drag.XAxis
    drag.minimumX: 0
    drag.maximumX: _area.totalWidth
    acceptedButtons: Qt.LeftButton | Qt.RightButton

    onClicked: (mouse) => {
                   if(mouse.button === Qt.RightButton)
                   {
                       contextMenu.x = mouse.x
                       contextMenu.y = mouse.y
                       contextMenu.open()
                   }
               }

    ToolTip.text: "%1\n%2".arg(_area.title).arg(_area.desc)
    Rectangle {
        anchors.fill: parent
        radius: _area.itemHeight / 2
        color: _area.color
        clip: true

        Label {
            id: _label
            anchors.centerIn: parent
            text: _area.title
            visible: !_area.isRound
        }
        Image {
            id: _img
            anchors.fill: parent
            sourceSize.height: height
            sourceSize.width: width
            fillMode: Image.PreserveAspectFit
            visible: source && _area.isRound
        }
    }

    Menu {
        id: contextMenu
        MenuItem {
            text: _area.lock ? "Unlock" : "Lock"
            onTriggered: _area.lock = !_area.lock
        }
        MenuItem {
            text: "Down"
            onTriggered: _area.row = _area.row+1
        }
        MenuItem {
            text: "Up"
            onTriggered: _area.row = _area.row-1
        }
    }
}
