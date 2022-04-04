import QtQuick
import QtQuick.Controls

Row {
    id: _root
    Label {
        text: "Printemps"
        width: _root.width/4
        height: _root.height
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter
        background: Rectangle {
            color: Qt.darker("green")
            opacity: 0.4
        }
    }
    Label {
        text: "Été"
        width: _root.width/4
        height: _root.height
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter
        background: Rectangle {
            color: Qt.lighter("green")
            opacity: 0.4
        }
    }
    Label {
        text: "Automne"
        width: _root.width/6
        height: _root.height
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter
        background: Rectangle {
            color: "orange"
            opacity: 0.4
        }
    }
    Label {
        text: "Hiver"
        height: _root.height
        width: _root.width/3
        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter
        background: Rectangle {
            color: "lightgray"
            border.width: 1
            opacity: 0.4
        }
    }
}
