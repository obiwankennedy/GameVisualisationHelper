import QtQuick
import QtQuick.Window
import QtQuick.Layouts
//import QtGraphicalEffects 1.0
import QtQuick.Controls
import Controller

ApplicationWindow {
    id: root
    x: 0
    y: 0
    width: 1920
    height: 1080



    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width
    visible: true
    title: "GameVisualHelper"
    property bool deco: true

    onClosing: Qt.quit()
    flags: Qt.Window //deco ? Qt.Window : Qt.FramelessWindowHint

    Item {
        id: main
        anchors.fill: parent

        states: [
            State {
                name: "Normal"
                when: MainController.previewCtrl.currentMode === 1
                PropertyChanges {
                    target: _content
                    panel: 1
                }
                PropertyChanges {
                    target: _avatarPanel
                    visible: true
                }
            },
            State {
                name: ""
                when: MainController.previewCtrl.currentMode === 0
                PropertyChanges {
                    target: _avatarPanel
                    visible: false
                }
                PropertyChanges {
                    target: _content
                    panel: 0
                }
            },
            State {
                name: "diaporama"
                when: MainController.previewCtrl.currentMode === 4
                PropertyChanges {
                    target: _content
                    panel: 2
                }
                PropertyChanges {
                    target: _avatarPanel
                    visible: true
                }
            },
            State {
                name: "carousel"
                when: MainController.previewCtrl.currentMode === 5
                PropertyChanges {
                    target: _content
                    panel: 4
                }
                PropertyChanges {
                    target: _avatarPanel
                    visible: true
                }
            },
            State {
                name: "Ouvert"
                when: MainController.previewCtrl.currentMode === 3
                PropertyChanges {
                    target: _content
                    panel: 3
                }
                PropertyChanges {
                    target: _avatarPanel
                    visible: true
                }
            },
            State {
                name: "Carte"
                when: MainController.previewCtrl.currentMode === 2
                PropertyChanges {
                    target: _content
                    panel: 5
                }
                PropertyChanges {
                    target: _avatarPanel
                    visible: true
                }
            },
            State {
                name: "Gridview"
                when: MainController.previewCtrl.currentMode === 6
                PropertyChanges {
                    target: _content
                    panel: 6
                }
                PropertyChanges {
                    target: _avatarPanel
                    visible: true
                }
            },
            State {
                name: "Sheet"
                when: MainController.previewCtrl.currentMode === 7
                PropertyChanges {
                    target: _content
                    panel: 7
                }
                PropertyChanges {
                    target: _avatarPanel
                    visible: true
                }
            }
        ]



        Image {
            anchors.fill: parent
            source: "qrc:/resources/L5RRiz/wallpaper.png"
        }

        RowLayout {
            id: _avatarPanel
            visible: false
            anchors.fill: parent
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            CharacterItem {
                Layout.topMargin: 420
                character: MainController.gameMaster
                Layout.alignment: Qt.AlignTop
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            ColumnLayout {
                Layout.fillHeight: true
                Layout.topMargin: 150
                CharacterItem {
                    character: MainController.characterTwo
                    visible: !MainController.characterTwo.hidden
                    reverse: true
                }
                CharacterItem {
                    character: MainController.characterOne
                    visible: ! MainController.characterOne.hidden
                    reverse: true
                }
                CharacterItem {
                    character: MainController.characterThree
                    visible: !MainController.characterThree.hidden
                    reverse: true
                }
                CharacterItem {
                    character: MainController.characterFour
                    visible: !MainController.characterFour.hidden
                    reverse: true
                }
                CharacterItem {
                    character: MainController.characterFifth
                    visible: MainController.characterFifth && !MainController.characterFifth.hidden
                    reverse: true
                }
            }
        }





        MouseArea {
            anchors.fill:parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: (mouse)=> {
                if (mouse.button == Qt.LeftButton)
                    root.deco = !root.deco
                else if(mouse.button == Qt.RightButton)
                    menu.popup()
            }

            Menu {
                id: menu
                Action  {
                    text: "1. En attentes"
                    checkable: true
                    checked: main.state === ""
                    onTriggered: MainController.previewCtrl.currentMode = 0//main.state = ""
                }
                Action  {
                    text: "2. Normal"
                    checkable: true
                    checked: main.state === "Normal"
                    onTriggered: MainController.previewCtrl.currentMode = 1
                }
                Action  {
                    text: "3. Carte"
                    checkable: true
                    checked: main.state === "Carte"
                    onTriggered: MainController.previewCtrl.currentMode = 2
                }
                Action  {
                    text: "4. Ouvert"
                    checkable: true
                    checked: main.state === "Ouvert"
                    onTriggered: MainController.previewCtrl.currentMode = 3
                }
                Action  {
                    text: "5. Diaporama"
                    checkable: true
                    checked: main.state === "diaporama"
                    onTriggered: MainController.previewCtrl.currentMode = 4
                }
                Action  {
                    text: "6. Carousel"
                    checkable: true
                    checked: main.state === "carousel"
                    onTriggered: MainController.previewCtrl.currentMode = 5
                }
                Action  {
                    text: "7. Gridview"
                    checkable: true
                    checked: main.state === "Gridview"
                    onTriggered: MainController.previewCtrl.currentMode = 6
                }
                Action  {
                    text: "8. Sheet"
                    checkable: true
                    checked: main.state === "Sheet"
                    onTriggered: MainController.previewCtrl.currentMode = 7
                }

            }
        }

        CenterContent {
            id: _content
            visible: true
            anchors.centerIn: parent
            width: parent.width*0.7
            height: parent.height

        }

        Label {
            id: timetracker
            property date currentDate: new Date()
            font.pixelSize: 20
            font.weight: Font.Bold
            text: "%1 - %2".arg(currentDate.toLocaleDateString(Qt.locale("fr_FR"), "dd.MM.yyyy"))
                           .arg(currentDate.toLocaleTimeString(Qt.locale("fr_fr"),"hh:mm"))
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            Timer {
                running: true
                repeat: true
                interval: 1000*15
                onTriggered: {
                    timetracker.currentDate = new Date()
                }
            }
        }

    }

}
