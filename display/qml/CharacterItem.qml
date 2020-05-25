import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0


Frame {
    id: root
    property QtObject character
    layer.enabled: true
    layer.effect: DropShadow {
      horizontalOffset: 3
      verticalOffset: 3
      radius: 8.0
      samples: 17
      color: "#aa000000"
    }

    ColumnLayout{
        id: col
        anchors.fill: parent
        Image {
            id: img
            source: root.character.imgId
            fillMode: Image.PreserveAspectFit
            Layout.fillHeight: true
            Layout.fillWidth: true
            sourceSize.height: 180
            layer.enabled: true
            layer.effect: Colorize {
                hue: 0.0
                saturation: 0
                lightness: 0
                visible: !root.character.isSpeaking
                layer.enabled: true
                layer.effect: OpacityMask {
                    maskSource:  Rectangle {
                        width: img.width
                        height: img.height
                        radius: 10
                        //visible: false
                    }
                }
            }


        }
        Item {
            Layout.fillWidth: true
            Rectangle {
                id: line
                height: 1
                width: parent.width*(root.character.speakingTime / _model.maxSpeakingTime)
                color:"orange"
                layer.enabled: true
                layer.effect:Glow {
                    radius: 8
                    samples: 17
                    color: "orange"
                }
            }
        }
        Label {
            text: root.character.name
            Layout.alignment: Qt.AlignCenter
            color: "white"
        }
    }

    background: Rectangle {
        color: root.character.isSpeaking ? root.character.color : "black"
        radius: 10
    }
}
