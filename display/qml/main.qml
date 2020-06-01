import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls 2.4

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
    property var imgModel: ["qrc:/resources/lg/landscape/bostonpanneau.jpg","qrc:/resources/lg/landscape/building2.jpg","qrc:/resources/lg/landscape/bunker_hill_monument.jpg","qrc:/resources/lg/landscape/horizon.jpg","qrc:/resources/lg/landscape/latinSchool.jpg","qrc:/resources/lg/landscape/old_state_house.jpg","qrc:/resources/lg/landscape/port1.jpg","qrc:/resources/lg/landscape/harvard.webp"]


    flags: deco ? Qt.Window : Qt.FramelessWindowHint

    Item {
        id: main
        anchors.fill: parent

        states: [
            State {
                name: ""
                PropertyChanges {
                    target:waitingPanel
                    visible: false
                }
                PropertyChanges {
                    target: diapoPanel
                    visible: false
                }
                PropertyChanges {
                    target: greenScreen
                    visible: false
                }

            },
            State {
                name: "onhold"
                PropertyChanges {
                    target:waitingPanel
                    visible: true
                }
                PropertyChanges {
                    target: diapoPanel
                    visible: false
                }
                PropertyChanges {
                    target: greenScreen
                    visible: false
                }
            },
            State {
                name: "diaporama"
                PropertyChanges {
                    target:waitingPanel
                    visible: false
                }
                PropertyChanges {
                    target: diapoPanel
                    visible: true
                }
                PropertyChanges {
                    target: greenScreen
                    visible: false
                }
            },
            State {
                name: "carousel"
                PropertyChanges {
                    target:waitingPanel
                    visible: false
                }
                PropertyChanges {
                    target: diapoPanel
                    visible: true
                }
                PropertyChanges {
                    target: greenScreen
                    visible: false
                }
            },
            State {
                name: "Ouvert"
                PropertyChanges {
                    target:waitingPanel
                    visible: false
                }
                PropertyChanges {
                    target: diapoPanel
                    visible: false
                }
                PropertyChanges {
                    target: greenScreen
                    visible: true
                }
            }
        ]



        Image {
            anchors.fill: parent
            source: "qrc:/resources/lg/fond.png"
        }

        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            CharacterItem {
                Layout.topMargin: 20
                character: _obi
                Layout.alignment: Qt.AlignTop
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            ColumnLayout {
                Layout.fillHeight: true
                CharacterItem {
                    character: _xelal
                }
                CharacterItem {
                    character: _chewba
                }
                CharacterItem {
                    character: _alci
                }
                CharacterItem {
                    character: _captain
                }
            }
        }

        Label {
            id: waitingPanel
            anchors.centerIn: parent
            text: "Le liveplay va démarrer d'ici quelques instants.\nMerci de votre patience."
            font.pixelSize: 70
            visible:false
        }

        ImageView {
            id: diapoPanel
            anchors.centerIn: parent
            model: imgModel
            width: parent.width * 0.5
            height: parent.height * 0.5
            visible:false
        }

        ImagePathView {
            id: imagePathPanel
            anchors.centerIn: parent
            width: parent.width * 0.5
            height: parent.height * 0.5
            visible: false
        }


        Rectangle {
            id: greenScreen
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            color: "#00FF00"
            width: parent.width * 0.7
            height: parent.height * 0.7
            visible: false
        }




        MouseArea {
            anchors.fill:parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                if (mouse.button == Qt.LeftButton)
                    root.deco = !root.deco
                else if(mouse.button == Qt.RightButton)
                    menu.popup()
            }

            Menu {
                id: menu
                Action  {
                    text: "En attentes"
                    onTriggered: main.state = "onhold"
                }
                Action  {
                    text: "Diaporama"
                    onTriggered: main.state = "diaporama"
                }
                Action  {
                    text: "Carousel"
                    onTriggered: main.state = "carousel"
                }
                Action  {
                    text: "Ouvert"
                    onTriggered: main.state = "Ouvert"
                }
                Action  {
                    text: "Normal"
                    onTriggered: main.state = ""
                }
            }
        }
    }

}
