import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Controller

Item {
    Rectangle {
        anchors.fill: parent
        color: "white"
        opacity: 0.5
    }
    GridView {
        id: _grid
        anchors.fill: parent
        model: MainController.carouselModel


        Component {
            id: delegateImg
            Image {
                id: _img
                width: 200
                height: 200
                source: model.path
                fillMode: Image.PreserveAspectFit
            }
        }

        cellWidth: 200
        cellHeight: 200
        delegate: delegateImg


    }
}


