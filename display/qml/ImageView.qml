import QtQuick
import QtQuick.Controls


ListView {
    id: _root
    interactive: false

    delegate: Image {
        height: _root.height
        width: _root.width
        fillMode: Image.PreserveAspectFit
        visible: _root.currentIndex == index
        source: model.path
    }
}
