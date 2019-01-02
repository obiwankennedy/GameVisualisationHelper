import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.0

ApplicationWindow {
    id: root
    x: 2560+1920-width
    y: 5
    width: 1000
    height: 200
    visible: true
    title: "GameVisualHelper"
    property bool deco: true


    flags: deco ? Qt.WindowStaysOnTopHint : Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

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
                    color: "transparent"//img.lenght() > 0 ? "transparent" : colorCh
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
                    color: isSpeaking ? colorCh : "black"
                }
                Text {
                    anchors.centerIn:rect
                    color: "white"
                    font.bold: true
                    text: name
                }
                Rectangle {
                    id: line
                    anchors {
                        bottom: parent.children[0].bottom
                        bottomMargin: 3
                        left: parent.left
                    }
                    height: 1
                    width: parent.width*percent
                    color:"orange"
                }
                Glow {
                    anchors.fill: line
                    radius: 8
                    samples: 17
                    color: "orange"
                    source: line
                }
            }

        }
    }
    MouseArea {
        anchors.fill:parent
//        property int previousX : 0
//        property int previousY : 0
        //drag.target: root
        onClicked: root.deco = !root.deco
        /*onPressed: {
            previousX = mouse.x
            previousY = mouse.y
            parent.focus = true
        }
        onPositionChanged: {
            console.log(previousX+" "+mouse.x+" "+(mouse.x-previousX))
            root.x += mouse.x-previousX
            root.y += mouse.y-previousY
            previousX = mouse.x
            previousY = mouse.y
        } */
    }

}
