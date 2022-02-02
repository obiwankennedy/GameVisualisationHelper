import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
//import QtGraphicalEffects 1.0
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
        Rectangle {
            Layout.preferredHeight: 150
            Layout.preferredWidth: 150
            Layout.alignment: Qt.AlignHCenter
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
                /*gl_FragColor = vec4(vec3(dot(tex.rgb,
                                    vec3(0.344, 0.5, 0.156))),
                                         tex.a) * qt_Opacity;*/
            }
            /*ShaderEffect {
                anchors.fill: img
                property variant src: img
                visible: !_root.character.isSpeaking
                vertexShader: "
                                uniform highp mat4 qt_Matrix;
                                attribute highp vec4 qt_Vertex;
                                attribute highp vec2 qt_MultiTexCoord0;
                                varying highp vec2 coord;
                                void main() {
                                    coord = qt_MultiTexCoord0;
                                    gl_Position = qt_Matrix * qt_Vertex;
                                }"
                fragmentShader: "
                    varying highp vec2 coord;
                    uniform sampler2D src;
                    uniform lowp float qt_Opacity;
                    void main() {
                        lowp vec4 tex = texture2D(src, coord);
                        gl_FragColor = vec4(vec3(dot(tex.rgb,
                                            vec3(0.344, 0.5, 0.156))),
                                                 tex.a) * qt_Opacity;
                    }"
            }*/
               // layer.enabled: !_root.character.isSpeaking
                /*layer.effect: Colorize {
                    hue: 0.0
                    saturation: 0
                    lightness: 0
                    layer.enabled: true
                    layer.effect: OpacityMask {
                        maskSource:  Rectangle {
                            width: img.width
                            height: img.height
                            radius: 10
                            //visible: false
                        }
                    }
                }*/
        }
        Item {
            Layout.fillWidth: true
            Rectangle {
                id: line
                height: 1
                width: parent.width*(_root.character.speakingTime / MainController.maxSpeakingTime)
                color:"orange"
                /*layer.enabled: true
                layer.effect:Glow {
                    radius: 8
                    samples: 17
                    color: "orange"
                }*/
            }
        }
        Image {
            Layout.alignment: Qt.AlignCenter
            Layout.topMargin: -20
            source: "qrc:/resources/L5RRiz/header.png"
            sourceSize.width: 300
            //rotation: _root.reverse ? 180 : 0
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
