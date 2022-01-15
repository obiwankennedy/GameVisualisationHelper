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

    Timer {
        running: _root.visible
        repeat: true
        interval: 5000
        onTriggered: {
            _root.currentIndex+=1

            if(_root.currentIndex > _root.count)
                _root.currentIndex = 0

        }
    }
}
