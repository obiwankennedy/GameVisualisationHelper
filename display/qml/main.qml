import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.0

ApplicationWindow {
    id: root
    width: 1000
    height: 200
    visible: true
    title: "GameVisualHelper"

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    RowLayout {
        anchors.fill: parent
        Repeater {
            model: _model
            Item {
                Layout.fillHeight: true
                Layout.preferredWidth: parent.height * children[0].sourceSize.width / children[0].sourceSize.height
                Image {
                    id: avatar
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: img
                    horizontalAlignment: Image.AlignLeft
                    verticalAlignment: Image.AlignTop
                }
                Colorize {
                    anchors.fill: parent.children[0]
                    source: parent.children[0]
                    hue: 0.0
                    saturation: 0
                    lightness: 0
                    visible: !isSpeaking
                }
                Rectangle {
                    id: border
                    color: "transparent"
                    anchors.fill: avatar
                    border.width: 4
                    border.color: colorCh
                    visible: isSpeaking
                }

                Rectangle {
                    id: rect
                    anchors {
                        bottom: parent.children[0].bottom
                        left: parent.left
                        right: parent.right
                    }
                    height: parent.height*0.2
                    color:"black"
                }
                Text {
                    anchors.centerIn:rect
                    color: "white"
                    font.bold: true
                    text: name
                }
            }

        }
    }

}
