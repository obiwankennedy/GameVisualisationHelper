import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Window
import Qt.labs.platform as Platform
import Controller

Item {
    id: _root
    property real year: _yearCount.value
    property real yearScale: _scale.value
    property real totalWidth: year*yearScale

    property real itemHeight: 40

    Platform.ColorDialog {
        id: _colorDiag
        title: "Select color"
        /*onAccepted: {
            _button.bgColor = _colorDiag.color
        }*/
    }

    Dialog {
        id: _addItem
        title: "Add "
        parent: Overlay.overlay
        anchors.centerIn: parent
        GridLayout {
            columns: 2
            Label {
                text: "Titre:"

            }
            TextField {
                id: _title
                Layout.fillWidth: true
            }

            Label {
                text: "Description"
            }
            TextArea {
                id: _desc
                Layout.fillWidth: true
            }

            Label {
                text: "démarrage: Année"
            }
            SpinBox {
                id: _starty
                from: 1122
                to: 1122+_root.year
                editable: true
                Layout.fillWidth: true
            }

            Label {
                text: "démarrage: day"
            }
            SpinBox {
                id: _start
                from: 0
                to: 365
                editable: true
                Layout.fillWidth: true
            }


            Label {
                text: "durée: Month"
            }
            SpinBox {
                id: _durationM
                from: 0
                editable: true
                to: _root.year * 12
                Layout.fillWidth: true
            }
            Label {
                text: "durée: jour"
            }
            SpinBox {
                id: _duration
                from: 0
                editable: true
                to: 30
                Layout.fillWidth: true
            }
            Label {
                text: "Ligne"
            }
            SpinBox {
                id: _row
                from: 0
                to: 10
                Layout.fillWidth: true
            }
            Label {
                text: "table"
            }
            ComboBox {
                id: _table
                model: ["Toutes","table1","table2"]
                Layout.fillWidth: true
            }
            Label {
                text: "Couleur"
            }
            Button {
                id: _color
                Layout.fillWidth: true
                background: Rectangle {
                    color: _colorDiag.color
                }
                onClicked: {
                    _colorDiag.open()
                }
            }
        Button {
            text: "Ok"
            onClicked: _addItem.accept()
        }
        Button {
            text: "Cancel"
            onClicked: _addItem.reject()
        }

        }
        onAccepted: {
            MainController.calendarModel.append(_title.text, _desc.text, (_starty.value-1122)*365+_start.value, _durationM.value*30+_duration.value, _table.currentIndex, _row.value, _colorDiag.color)
        }
    }


    RowLayout {
        id: _toolbar
        height: 40
        width: parent.width
        Label {
            text:"Nombre d’années:"
        }
        SpinBox {
            id: _yearCount
            from: 1
            to: 25
            value: 8
        }
        Label {
            text: "Échelle d’une année: %1".arg(_scale.value)
            Layout.preferredWidth: 200
        }
        Slider {
            id: _scale
            from: 100
            to: 5000
            value: 2500
        }
        Button {
            text: "+"
            onClicked: _addItem.open()
        }
    }

    Flickable {
        anchors.top: _toolbar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        contentHeight: height
        contentWidth: _root.totalWidth
        Row {
            id: _yearLine
            width: _root.totalWidth
            height: _root.itemHeight
            Repeater {
                model: _root.year
                delegate: ItemDelegate {
                    width: _root.yearScale
                    height: _root.itemHeight
                    Label {
                        anchors.fill: parent
                        anchors.rightMargin: 1
                        horizontalAlignment: Label.AlignHCenter
                        verticalAlignment: Label.AlignVCenter
                        background: Rectangle {
                            color: index%2 == 0 ?"red" : "green"
                            opacity: 0.4
                        }
                        text: "%1".arg(1122+index)
                    }
                }
            }
        }
        Row {
            id: _seasonLine
            anchors.top: _yearLine.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: _root.itemHeight
            Repeater {
                model: _root.year
                delegate: Seasons {
                    width: _root.yearScale
                    height: _root.itemHeight
                }
            }
        }
        Row {
            id: _monthLine
            anchors.top: _seasonLine.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            Repeater {
                model: _root.year
                delegate: Months {
                    width: _root.yearScale
                    height: _root.itemHeight
                }
            }
        }
        Row {
            id: _eventLine
            anchors.top: _monthLine.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            Repeater {
                model: _root.year
                delegate: Celebrations {
                    width: _root.yearScale
                    height: _root.itemHeight
                }
            }
        }
        Item {
            id: _calendarItems
            anchors.top: _eventLine.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            property real dayScale: _root.yearScale/365

            Repeater {
                id: _grid
                anchors.fill: parent
                property real monthScale: _root.totalWidth/_root.year/12
                model: _root.year * 12
                Rectangle {
                    x: index * _grid.monthScale
                    width: 1
                    height: _calendarItems.height
                    color:"gray"
                    opacity: 0.5
                }
            }

            Repeater {
                id: _vGrid
                anchors.fill: parent
                model: _calendarItems.height/_root.itemHeight
                Rectangle {
                    y: index * _root.itemHeight
                    height: 1
                    width: _vGrid.width
                    color:"gray"
                    opacity: 0.5
                }
            }

            Repeater {
                model: MainController.calendarModel

                delegate: CalendarItem {
                    id: _item
                    Component.onCompleted: x= model.start * _calendarItems.dayScale
                    y: model.row * _root.itemHeight
                    onXChanged: model.start = x / _calendarItems.dayScale
                    height: _root.itemHeight
                    width: Math.max(model.duration * _calendarItems.dayScale, minimunWidth)
                    isRound: model.duration === 1
                    lock: model.lock
                    source: model.image
                    row: model.row
                    title: model.title
                    desc: model.desc
                    color: model.color
                    onLockChanged: model.lock = _item.lock
                    onRowChanged: model.row = _item.row
                    totalWidth: _root.totalWidth
                    itemHeight: _root.itemHeight

                    Connections {
                        target: _calendarItems
                        function onDayScaleChanged() {
                            _item.x= model.start * _calendarItems.dayScale
                        }
                    }

                }
            }
        }
    }

}
