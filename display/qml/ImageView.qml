import QtQuick
import QtQuick.Controls


Item {
    id: _root
    property alias model: _list.model

   Timer {
        running: true
        repeat: true
        interval: 2000
        onTriggered: {
            if(_list.currentIndex+1 == _list.count)
                _list.currentIndex = 0
            else
                _list.currentIndex +=1
        }
    }

    ListView {
        id: _list
        interactive: false
        delegate: Item {
            height: _root.height
            width: _root.width
            Component.onCompleted: _image.source = model.path
        }
    }
    Image {
        id: _image
        anchors.centerIn: parent
        height: _root.height*0.7
        width: _root.width*0.7
        fillMode: Image.PreserveAspectFit
    }
}
