import QtQuick
import QtQuick.Controls
import Controller
import QtWebEngine
import QtQuick.Layouts

Item {
    id: _root
    TabBar {
        id: _bar
        width: _root.width
        anchors.top: parent.top
        TabButton {
            text: MainController.characterOne.name
            width: Math.max(100, _bar.width / 4)
        }
        TabButton {
            text: MainController.characterTwo.name
            width: Math.max(100, _bar.width / 4)
        }
        TabButton {
            text: MainController.characterThree.name
            width: Math.max(100, _bar.width / 4)
        }
        TabButton {
            text: MainController.characterFour.name
            width: Math.max(100, _bar.width / 4)
        }
    }

    StackLayout {
        anchors.top: _bar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        currentIndex: _bar.currentIndex
        WebEngineView {
            id: first
            url: MainController.characterOne.sheet
        }
        WebEngineView {
            id: second
            url: MainController.characterTwo.sheet
        }
        WebEngineView {
            id: third
            url: MainController.characterThree.sheet
        }
        WebEngineView {
            id: fourth
            url: MainController.characterFour.sheet
        }
    }
}
