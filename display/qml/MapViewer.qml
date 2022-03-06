import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Controller

Item {
    id: _root
    property real factor: (1344/6187)

    Flickable {
        anchors.fill: parent
        focus: true
        interactive: true
        contentWidth:  _image.width
        contentHeight:  _image.height
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        Image {
            id: _image
            source: "file:///home/renaud/documents/03_jdr/01_Scenariotheque/16_l5r/01_resources/Carte/Rokugan-map2.svg"
            sourceSize.width: 6187*_root.factor
            sourceSize.height: 9381*_root.factor

            Repeater {
                model: MainController.proxyModel
                Token {
                    id: _token
                    x: model.position.x
                    y: model.position.y
                    source: img
                    color: model.colorCh
                    visible: !model.gameMaster
                    function updatePosition() {
                        if(/*model.position.x !== _token.x || model.position.y !== _token.y*/_token.dragged)
                            model.position = Qt.point(_token.x, _token.y)
                    }

                    onXChanged: updatePosition()
                    onYChanged: updatePosition()
                }
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
    }
}
