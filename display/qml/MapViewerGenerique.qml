import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.settings
import Controller

Item {
    id: _root
    property int imgWidth: 0
    property int imgHeight: 0
    property real factor: imgWidth == 0 ? 1 : (imgHeight/imgWidth)

    Flickable {
        anchors.fill: parent
        focus: true
        interactive: true
        contentWidth:  _image.width
        contentHeight:  _image.height
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        visible: _image.source
        Drag.active: dragHandler.active
        Drag.dragType: Drag.Automatic
        Drag.supportedActions: Qt.CopyAction
        Drag.mimeData: MainController.mimeData

        Settings {
            id: settings
            category: MainController.table1 ? "MapTable1" : "MapTable2"
            property alias imgSource: _image.source
        }

        Image {
            id: _image
            sourceSize.width: _root.imgWidth*_root.factor
            sourceSize.height: _root.imgHeight*_root.factor

            Repeater {
                model: MainController.proxyModel
                Token {
                    id: _token
                    x: model.positionBis.x * _root.factor
                    y: model.positionBis.y * _root.factor
                    property real revfactor: 1/_root.factor
                    source: img
                    color: model.colorCh
                    visible: !model.gameMaster
                    function updatePosition() {
                        if(_token.dragged)
                            model.positionBis = Qt.point(_token.x * _token.revfactor, _token.y * _token.revfactor)
                    }

                    onXChanged: updatePosition()
                    onYChanged: updatePosition()
                }
            }

        }


        DragHandler {
            id: dragHandler
            acceptedModifiers: Qt.ControlModifier
            acceptedButtons: Qt.LeftButton
            onActiveChanged:{
                _root.Drag.mimeData = MainController.mimeData
                if (active) {
                    _root.grabToImage(function(result) {
                        result.saveToFile(MainController.tempFile)
                        _root.Drag.imageSource = MainController.tempFile
                        MainController.refreshTempFile()
                    })
                }
            }
        }
    }



    MouseArea {
        id: _mArea
        anchors.fill: parent
        enabled: _rule.checked
        property point start
        property point end
        property real dist: 0.
        property real distKM: _mArea.dist * 202 / (1001*_root.factor) / 30
        acceptedButtons: Qt.LeftButton

        onPressed: (mouse)=> {
            start = Qt.point(mouse.x, mouse.y)
            if(_pwi.checked)
                _bigger.start()
        }

        onPositionChanged: (mouse)=>{
            end = Qt.point(mouse.x, mouse.y)
            _mArea.dist = Math.sqrt(Math.pow(Math.abs(end.x - start.x),2)+Math.pow(Math.abs(end.y - start.y),2))
                        console.log("Dist:",_mArea.dist)
            _canvas.requestPaint()
        }
        Canvas {
            id: _canvas
            anchors.fill: parent
            visible: _rule.checked
            onPaint: {
                console.log("Repaint")
                var ctx = getContext("2d");
                ctx.reset()
                ctx.save()
                ctx.fillStyle = Qt.rgba(0, 0, 0, 0);
                ctx.fillRect(0, 0, width, height);
                ctx.lineWidth = 1
                ctx.strokeStyle = Qt.rgba(1, 0, 0, 1);
                ctx.beginPath();
                ctx.moveTo(_mArea.start.x, _mArea.start.y)
                ctx.lineTo(_mArea.end.x, _mArea.end.y)
                ctx.closePath();
                ctx.restore()
                ctx.save()
                ctx.lineWidth = 3
                ctx.strokeText(_mArea.distKM.toFixed(1), _mArea.end.x, _mArea.end.y);
                ctx.restore()
                ctx.stroke();
            }
        }
        Rectangle {
            x: parent.start.x-width/2
            y: parent.start.y-width/2
            width: 0
            height: width
            radius: width/2
            border.width: 5
            border.color: "green"
            visible: _pwi.checked

            NumberAnimation {
                id: _bigger
                loops: 4
                target: parent
                property: "width"
                duration: 400
                to: 200
                easing.type: Easing.InOutQuad
            }


        }
    }

    DropArea {
        id: _drop
        anchors.fill: parent
        enabled: true
        Rectangle {
                anchors.fill: parent
                color: "darkgreen"
                visible: parent.containsDrag && !_drop.drag.source
        }
        onDropped:(drop)=>{
                _image.source= drop.urls[0]
        }
        Drag.dragType: Drag.Automatic
    }

    RowLayout {
        visible: false
        Button {
            text: "mini"
            checkable: true
            checked: _root.factor===(360/3127)
            onClicked: _root.factor=(360/3127)
        }
        Button {
            text: "moyen"
            checkable: true
            checked: _root.factor===(1344/6187)
            onClicked: _root.factor=(1344/6187)
        }
        Button {
            text: "moitié"
            checkable: true
            checked: _root.factor===0.5
            onClicked: _root.factor=0.5
        }
        Button {
            text: "à L'échelle"
            checkable: true
            checked: _root.factor===1
            onClicked: _root.factor=1
        }
        Button {
            id: _rule
            text: "règle"
            checkable: true

        }
        Button {
            id: _pwi
            text: "Pointer"
            checkable: true
        }
    }
}
