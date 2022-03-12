import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Controller

Item {
    id: _root
    Rectangle {
        anchors.fill: parent
        color: "white"
        opacity: 0.5
    }
    Popup {
        id: _bigPic
        width: 200
        height: 200
        padding: 0
        property alias source: _imgBig.source
        property alias name: _label.text
        property alias textSize: _label.font.pixelSize
        property alias bgOpacity: _bg.opacity
        property real originX: 0
        property real originY: 0
        closePolicy: Popup.NoAutoClose
        background: Rectangle {
            id: _bg
            color: "white"
            opacity: 0.0
        }
        MouseArea {
            anchors.fill: parent
            Image {
                id: _imgBig
                 anchors.fill: parent
                 fillMode: Image.PreserveAspectFit
                 Label {
                     id: _label
                     anchors.bottom: parent.bottom
                     anchors.left: parent.left
                     anchors.right: parent.right
                     horizontalAlignment: Text.AlignHCenter
                     background: Rectangle {
                         color: "white"
                         opacity: 0.8
                     }
                 }
            }
            onClicked:  {
                if(_growing.running)
                    _growing.stop()
                _reducing.start()

            }
        }

        onVisibleChanged:{
            if(visible)
              _growing.start()
        }
        //onVisibleChanged:
        ParallelAnimation {
            id: _growing
            NumberAnimation {
                target: _bigPic
                property: "x"
                to: 0.
                duration: 2000
                easing.type: Easing.InOutQuad
            }
            NumberAnimation {
                target: _bigPic
                property: "y"
                to: 0.
                duration: 2000
                easing.type: Easing.InOutQuad
            }
            NumberAnimation {
                target: _bigPic
                property: "width"
                to: _root.width
                duration: 2000
                easing.type: Easing.InOutQuad
            }
            NumberAnimation {
                target: _bigPic
                property: "height"
                to: _root.height
                duration: 2000
                easing.type: Easing.InOutQuad
            }
            NumberAnimation {
                target: _bigPic
                property: "textSize"
                to: 40
                duration: 2000
                easing.type: Easing.InOutQuad
            }
            NumberAnimation {
                target: _bigPic
                property: "bgOpacity"
                to: 1.
                duration: 2000
                easing.type: Easing.InOutQuad
            }
        }
        SequentialAnimation {
            id: _reducing
            ParallelAnimation {
                NumberAnimation {
                    target: _bigPic
                    property: "x"
                    to: _bigPic.originX
                    duration: 2000
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: _bigPic
                    property: "y"
                    to: _bigPic.originY
                    duration: 2000
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: _bigPic
                    property: "width"
                    to: 200
                    duration: 2000
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: _bigPic
                    property: "height"
                    to: 200
                    duration: 2000
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: _bigPic
                    property: "textSize"
                    to: 14
                    duration: 2000
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: _bigPic
                    property: "bgOpacity"
                    to: 0.
                    duration: 2000
                    easing.type: Easing.InOutQuad
                }
            }
            PropertyAction {
                target: _bigPic
                property: "visible"
                value: false
            }
        }
    }

    GridView {
        id: _grid
        anchors.centerIn: parent
        width: 1200
        height: parent.height
        model: MainController.carouselModel


        Component {
            id: delegateImg
            MouseArea {
                id: _mouseArea
                width: 200
                height: 200
                Image {
                    id: _img
                    anchors.fill: parent
                    source: model.path
                    fillMode: Image.PreserveAspectFit
                    Label {
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        text: model.name
                        horizontalAlignment: Text.AlignHCenter
                        background: Rectangle {
                            color: "white"
                            opacity: 0.8
                        }
                    }
                }
                onClicked: {
                    _bigPic.bgOpacity = 0.0
                    _bigPic.originX = _mouseArea.x + _grid.x
                    _bigPic.originY =_mouseArea.y - _grid.contentY
                    _bigPic.width = _mouseArea.width
                    _bigPic.height = _mouseArea.height
                    _bigPic.x = _mouseArea.x + _grid.x
                    _bigPic.y = _mouseArea.y - _grid.contentY
                    _bigPic.source = model.path
                    _bigPic.name = model.name
                    _bigPic.open()
                }
            }
        }
        cellWidth: 200
        cellHeight: 200
        delegate: delegateImg
    }
}


