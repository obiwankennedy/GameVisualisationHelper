import QtQuick 2.12


Item {
    id: root
    property int imageIndex: 0
    property var model: ["qrc:/resources/lg/landscape/bostonpanneau.jpg","qrc:/resources/lg/landscape/building2.jpg","qrc:/resources/lg/landscape/bunker_hill_monument.jpg","qrc:/resources/lg/landscape/horizon.jpg","qrc:/resources/lg/landscape/latinSchool.jpg","qrc:/resources/lg/landscape/old_state_house.jpg","qrc:/resources/lg/landscape/port1.jpg","qrc:/resources/lg/landscape/harvard.webp"]
    Image {
        id: img
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        Behavior on opacity {
            PropertyAnimation {
                duration: 1000
            }
        }
    }
    Image {
        id: img2
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        Behavior on opacity {
            PropertyAnimation {
                duration: 1000
            }
        }
    }

    Timer {
        running: root.visible
        repeat: true
        interval: 5000
        onTriggered: {
            root.imageIndex+=1

            if(root.imageIndex > root.model.length)
                root.imageIndex = 0

            if(img.opacity > 0.5)
            {
                img2.source = root.model[root.imageIndex]
                img.opacity = 0.0
                img2.opacity = 1.0
            }
            else
            {
                img.source = root.model[root.imageIndex]
                img2.opacity = 0.0
                img.opacity = 1.0
            }
        }
    }
}
