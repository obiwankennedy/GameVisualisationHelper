import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Controller
import "Effect01/export"

Frame {
    id: _root
    property bool reverse: false
    property QtObject character

    width: 150
    height: 150

    padding: 0

    background: Item {
    }

    ColumnLayout{
        id: col
        anchors.fill: parent
        RowLayout {
            layoutDirection: reverse ? Qt.RightToLeft : Qt.LeftToRight
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            Item {
                Layout.preferredWidth: 8
                Layout.preferredHeight: 150
                RectangularGlow {
                    id: glowRect
                    glowRadius: 10
                    spread: 0.2
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    width: 8
                    //property real factor: 1.0
                    height: 150*(_root.character.speakingTime / MainController.maxSpeakingTime)
                    /*Timer {
                        running: true
                        repeat: true
                        onTriggered: {
                            console.log("factor:",glowRect.factor)
                            glowRect.factor = (glowRect.factor >= 1.0) ? 0.0 : glowRect.factor+0.05
                        }
                    }*/

                    color: _root.character.color
                    cornerRadius: 2 + glowRadius
                }
            }

            Rectangle {
                Layout.preferredHeight: 150
                Layout.preferredWidth: 150
                color: _root.character.isSpeaking ? _root.character.color : "black"
                Image {
                    id: img
                    source: _root.character.imgId
                    fillMode: Image.PreserveAspectFit
                    anchors.fill: parent
                    anchors.margins: 5
                    sourceSize.height: 150
                    layer.enabled: !_root.character.isSpeaking
                    layer.effect: ShaderEffect {
                        fragmentShader: "grayscale.frag.qsb"
                    }
                }
            }
        }
        Image {
            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: -20
            source: "qrc:/resources/L5RRiz/header.png"
            sourceSize.width: 300
            mirror: _root.reverse
            Label {
                text: _root.character.name
                color: "white"
                font.family: "Present LT BlackCondensed"
                font.pixelSize: 20
                anchors.centerIn: parent
            }
        }
    }
}
