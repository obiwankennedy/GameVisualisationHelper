import QtQuick
import QtQuick.Controls
import Controller

Item {
    id: _root
    property int panel: 0

    onPanelChanged: {
        _stack.clear()
        switch(_root.panel)
        {
        case 0:
            _stack.push(hold)
            break;
        case 1:
            _stack.push(normal)
            break;
        case 2:
            _stack.push(diapo)
            break;
        case 3:
            _stack.push(green)
            break;
        case 4:
            _stack.push(carousel)
            break;
        case 5:
            _stack.push(carte)
            break;
        case 6:
            _stack.push(grid)
            break;
        }
    }

    StackView {
        id: _stack
        anchors.fill: parent
        initialItem: hold
    }

    Component {
        id: normal
        Item {}
    }
    Component {
        id: diapo
        ImageView {
            id: diapoPanel
            model: MainController.diaporamaModel
        }
    }

    Component {
        id: green
        Rectangle {
            id: greenScreen
            color: "#00FF00"
        }
    }
    Component {
        id: grid
        GridGallery {
            id: gridScreen
        }
    }

    Component {
        id: carte
        MapViewer {
            id: mapScreen
        }
    }

    Component {
        id: hold
        Item {
            CustomFrame {
                id: waitingPanel
                anchors.centerIn: parent
                width: implicitWidth
                height: implicitHeight
                text: "Le liveplay va démarrer d'ici quelques instants.\nMerci de votre patience."
            }
        }

    }

    Component {
        id: carousel
        ImagePathView {
            id: imagePathPanel
        }
    }


}
