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
    //property var imgModel: ["qrc:/resources/lg/landscape/bostonpanneau.jpg","qrc:/resources/lg/landscape/building2.jpg","qrc:/resources/lg/landscape/bunker_hill_monument.jpg","qrc:/resources/lg/landscape/horizon.jpg","qrc:/resources/lg/landscape/latinSchool.jpg","qrc:/resources/lg/landscape/old_state_house.jpg","qrc:/resources/lg/landscape/port1.jpg","qrc:/resources/lg/landscape/harvard.webp"]


    onClosing: Qt.quit()
    flags: deco ? Qt.Window : Qt.FramelessWindowHint

    Item {
        id: main
        anchors.fill: parent

        states: [
            State {
                name: "Normal"
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
                    onTriggered: main.state = ""
                }
                Action  {
                    text: "2. Normal"
                    checkable: true
                    checked: main.state === "Normal"
                    onTriggered: main.state = "Normal"
                }
                Action  {
                    text: "3. Carte"
                    checkable: true
                    checked: main.state === "Carte"
                    onTriggered: main.state = "Carte"
                }
                Action  {
                    text: "4. Ouvert"
                    checkable: true
                    checked: main.state === "Ouvert"
                    onTriggered: main.state = "Ouvert"
                }
                Action  {
                    text: "5. Diaporama"
                    checkable: true
                    checked: main.state === "diaporama"
                    onTriggered: main.state = "diaporama"
                }
                Action  {
                    text: "6. Carousel"
                    checkable: true
                    checked: main.state === "carousel"
                    onTriggered: main.state = "carousel"
                }
                Action  {
                    text: "7. Gridview"
                    checkable: true
                    checked: main.state === "Gridview"
                    onTriggered: main.state = "Gridview"
                }
                Action  {
                    text: "8. Sheet"
                    checkable: true
                    checked: main.state === "Sheet"
                    onTriggered: main.state = "Sheet"
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
