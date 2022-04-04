import QtQuick
import QtQuick.Controls

Item {
    id: _root
    property real scaleDay: width/365
    property real yValue: Math.min(_root.height, _root.width)/2/2
    MouseArea {
        x: _root.scaleDay*1
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 1 du Lièvre: Jour de l'an"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }

    MouseArea {
        x: _root.scaleDay*43
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 13 du Dragon: 3-5-7 jour des enfants"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }

    MouseArea {
        x: _root.scaleDay*53
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 23 du dragon: Festival des bourgeons"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }

    MouseArea {
        x: _root.scaleDay*85
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 25 du Serpent: Festival des Iris"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }


    MouseArea {
        x: _root.scaleDay*96
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 6 du cheval: Festival des chrysentemes"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }

    MouseArea {
        x: _root.scaleDay*158
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 8 du Singe: Setsuban"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }


    MouseArea {
        x: _root.scaleDay*182
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 2 du Coq: Festival Kanto"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }

    MouseArea {
        x: _root.scaleDay*238
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 28 du Chien: Le Bon festival"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }

    MouseArea {
        x: _root.scaleDay*249
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 9 du Sanglier: Festival de la Rivière d’étoiles"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }

    MouseArea {
        x: _root.scaleDay*277
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 7 du Rat: Festival de la colère de la lune"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }

    MouseArea {
        x: _root.scaleDay*360
        y: _root.yValue
        width: Math.min(_root.height, _root.width)/2
        height: Math.min(_root.height, _root.width)/2
        ToolTip.visible: pressed
        ToolTip.text: "Le 28 du Tigre: Reveillon - Tochi no Ichi"
        Rectangle {
            anchors.fill: parent
            color: "yellow"
            border.width: 2
            border.color: "black"
            radius: Math.min(_root.height, _root.width)/4
        }
    }
}
