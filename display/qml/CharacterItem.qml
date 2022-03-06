import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import Controller

Frame {
    id: _root
    property bool reverse: false
    property QtObject character

    padding: 0

    background: Item {}

    ColumnLayout{
        id: col
        anchors.fill: parent
        RowLayout {
            layoutDirection: reverse ? Qt.RightToLeft : Qt.LeftToRight
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            Item {
                Layout.fillHeight: true
                Rectangle {
                    id: line
                    y: parent.height-height
                    height: parent.height*(_root.character.speakingTime / MainController.maxSpeakingTime)
                    width: 4
                    color: _root.character.color
                    layer.enabled: true
                    layer.effect:Glow {
                        radius: 28
                        spread: 0.8
                        color: _root.character.color
                        transparentBorder: true
                    }
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
