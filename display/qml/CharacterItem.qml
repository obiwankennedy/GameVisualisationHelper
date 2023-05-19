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

    /*Rectangle {
        id: frame

        width: 50
        height: parent.height
        color: "transparent"
        border.width: 1
        border.color: "black"
        Rectangle {
            id: line
            x: 23
            y: parent.height-height
            height: 150 //parent.height*(_root.character.speakingTime / MainController.maxSpeakingTime)
            width: 4
            color: _root.character.color
            radius: 2
            //layer.enabled: true
            / *layer.effect:  Glow {
                radius: 28
                spread: 0.8
                color: _root.character.color
                transparentBorder: true
            }* /
            //layer.effect:
        }
    }*/


    /*Rectangle {
        id: line
        x: 23
        y: _root.height-height
        opacity: 0.01
        height: 150 //parent.height*(_root.character.speakingTime / MainController.maxSpeakingTime)
        width: 4
        color: "white"//_root.character.color
        radius: 2
    }*/



    ColumnLayout{
        id: col
        anchors.fill: parent
        RowLayout {
            layoutDirection: reverse ? Qt.RightToLeft : Qt.LeftToRight
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
                /*Rectangle {
                    id: line
                    x: 23
                    y: parent.height-height
                    height: 150 //parent.height*(_root.character.speakingTime / MainController.maxSpeakingTime)
                    width: 4
                    color: _root.character.color
                    radius: 2
                    //layer.enabled: true
                    /*layer.effect:  Glow {
                        radius: 28
                        spread: 0.8
                        color: _root.character.color
                        transparentBorder: true
                    }* /
                    //layer.effect:
                }*/
            RectangularGlow {
                glowRadius: 10
                spread: 0.2
                y: _root.height-height
                //width: 8
                Layout.preferredWidth: 8
                height: 150 //parent.height*(_root.character.speakingTime / MainController.maxSpeakingTime)
                color: _root.character.color
                //transparentBorder: true
                cornerRadius: 2 + glowRadius
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

/*  Effect01 {
      source: line
      anchors.fill: parent
  }

  BlurHelper {
      id: blurHelper
      anchors.fill: frame
      source: frame
      //property int blurMax: 64
      //property real blurMultiplier: rootItem.blurMultiplier
  }

  ShaderEffect {
      readonly property Item iSource: frame
      readonly property Item iSourceBlur1: blurHelper.blurSrc1
      readonly property Item iSourceBlur2: blurHelper.blurSrc2
      readonly property Item iSourceBlur3: blurHelper.blurSrc3
      readonly property Item iSourceBlur4: blurHelper.blurSrc4
      readonly property Item iSourceBlur5: blurHelper.blurSrc5
      readonly property real blurMultiplier: 1.486
      readonly property real fastBlurAmount: 0.544753

      visible: true
      vertexShader: "qrc:/qml/glow.vert.qsb"
      fragmentShader: "qrc:/qml/glow.frag.qsb"
      anchors.fill: frame
  }*/
