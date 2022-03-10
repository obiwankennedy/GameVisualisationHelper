import QtQuick
import Controller
import QtQuick.Controls

PathView {
    id: view
    //pathItemCount: 7
    //preferredHighlightBegin: 0.5                         //
    //preferredHighlightEnd: 0.5                           // That should center the current item
    //highlightRangeMode: PathView.StrictlyEnforceRange    //

    Component {
        id: delegate
        Item {
            width: parent.width*0.8
            height: parent.height*0.8
            property double rotationValue2: PathView.itemRotation
            scale: PathView.iconScale
            opacity: PathView.isCurrentItem ? PathView.itemOpacity : 0.1
            z: PathView.isCurrentItem ? 5 : 0
            transform: Rotation {
                origin.x: width /2
                origin.y: height/2
                axis { x: 0; y: 1; z: 0 }
                angle: rotationValue2;
            }
            Image {
                id: _img
                anchors.fill: parent
                source: model.path
                fillMode: Image.PreserveAspectFit
            }
            Label {
                anchors.top: _img.bottom
                anchors.horizontalCenter: _img.horizontalCenter
                font.pointSize: 30
                text: model.name
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    view.currentIndex = index;
                }
            }

        }
    }
    model: MainController.carouselModel
    delegate: delegate
    focus: true
    Keys.onLeftPressed: incrementCurrentIndex()
    Keys.onRightPressed: decrementCurrentIndex()

    path: Path {
        startX: view.width/2
        startY: view.height/2
        PathAttribute { name: "iconScale"; value: 1.0 }
        PathAttribute { name: "itemOpacity"; value: 1 }
        PathAttribute { name: "itemRotation"; value: 0.0 }
        PathLine { x:view.width; y: 3*view.height/8 }
        PathAttribute { name: "iconScale"; value: 0.3 }
        PathAttribute { name: "itemOpacity"; value: 0.001 }
        PathAttribute { name: "itemRotation"; value: -54 }
        PathLine { x: 0; y: 3*view.height/8; }
        PathAttribute { name: "iconScale"; value: 0.3 }
        PathAttribute { name: "itemOpacity"; value: 0.001 }
        PathAttribute { name: "itemRotation"; value: 54 }
        PathLine { x: view.width*0.5; y: view.height*0.5; }
    }

    /*path: Path {
        startX: 0; startY: view.height/2
        PathAttribute { name: "iconScale"; value: 0.2 }
        PathAttribute { name: "iconOpacity"; value: 10.2 }
        PathAttribute { name: "iconOrder"; value: 0 }
        PathLine {x: view.width / 2;
            y: view.height/2 }
        PathAttribute { name: "iconScale"; value: 1.2 }
        PathAttribute { name: "iconOpacity"; value: 1 }
        PathAttribute { name: "iconOrder"; value: 8 }
        PathLine {x: view.width;
            y: view.height/2 }
    }*/

    /*  Rectangle {
        anchors.fill: parent
        color: "blue"
        opacity: 0.3
    }*/
    /*  Timer {
        running:true
        repeat: true
        onTriggered: console.log(view.height," w:",view.width)
    }*/
}
