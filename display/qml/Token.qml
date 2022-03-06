import QtQuick 2.0

Rectangle {
    id: _root
    property alias maxDragY: _dragArea.drag.maximumY
    property alias maxDragX: _dragArea.drag.maximumX
    property alias source: _img.source
    property alias dragged: _dragArea.drag.active
    radius: 10
    height: 60
    width: 60

    Drag.active: _dragArea.drag.active



    Image {
        id: _img
        anchors.centerIn: parent
        height: 50
        width: 50
        source: img
    }

    MouseArea {
        id: _dragArea
        anchors.fill: parent
        drag.target: parent
        drag.minimumX: 10
        drag.minimumY: 10
    }
}


