import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Controller

Item {
    id: _root
    property real factor: (1344/6187)

    Flickable {
        id: flick
        anchors.fill: parent
        focus: true
        interactive: true
        contentWidth:  _image.width
        contentHeight:  _image.height
        clip: true
        boundsBehavior: Flickable.StopAtBounds
        Drag.active: dragHandler.active
        Drag.dragType: Drag.Automatic
        Drag.supportedActions: Qt.CopyAction
        Drag.mimeData: MainController.mimeData

        Image {
            id: _image
            source: "file:///home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/01_resources/Carte/Rokugan-map2.svg"
            sourceSize.width: 6187*_root.factor
            sourceSize.height: 9381*_root.factor

            Repeater {
                model: MainController.proxyModel
                Token {
                    id: _token
                    x: model.position.x * _root.factor
                    y: model.position.y * _root.factor
                    property real revfactor: 1/_root.factor
                    source: img
                    color: model.colorCh
                    visible: !model.gameMaster
                    function updatePosition() {
                        if(_token.dragged)
                            model.position = Qt.point(_token.x * _token.revfactor, _token.y * _token.revfactor)
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
                flick.Drag.mimeData = MainController.mimeData
                if (active) {
                    flick.grabToImage(function(result) {
                        result.saveToFile(MainController.tempFile)
                        flick.Drag.imageSource = MainController.tempFile
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
            console.log("mouse vent")
            end = Qt.point(mouse.x, mouse.y)
            _mArea.dist = Math.sqrt(Math.pow(Math.abs(end.x - start.x),2)+Math.pow(Math.abs(end.y - start.y),2))
                        console.log("Dist:",_mArea.dist)
            _canvas.requestPaint()

            if((mouse.button == Qt.LeftButton) && (mouse.modifiers & Qt.ControlModifier))
            {
                console.log("grab image")
               flick.grabToImage(function(result) {
                   _mArea.image = result.image;
                   _mArea.drag.imageSource = result.url
                   _mArea.drag.startDrag()
                   // _img.Drag.imageSource = result.url;
               })
            }
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
       /* */
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

    RowLayout {
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
