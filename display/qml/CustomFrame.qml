import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

GridLayout {
        columns: 3
        columnSpacing: 0
        rowSpacing: 0
        property alias text: _central.text
        Image {
            source: "qrc:/resources/L5RRiz/cadre_0.png"
            //scale: 0.8
        }
        Image {
            source: "qrc:/resources/L5RRiz/cadre_1.png"
            Layout.fillWidth: true
            fillMode: Image.TileHorizontally
            //scale: 0.8
        }
        Image {
            source: "qrc:/resources/L5RRiz/cadre_2.png"
            //scale: 0.8
        }

        Image {
            source: "qrc:/resources/L5RRiz/cadre_3.png"
            //scale: 0.8
            Layout.fillHeight: true
            fillMode: Image.TileVertically
        }
        Label {
            id: _central
            font.family: "Present LT BlackCondensed"
            font.pixelSize: 70
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        Image {
            source: "qrc:/resources/L5RRiz/cadre_4.png"
            //scale: 0.8
            Layout.fillHeight: true
            fillMode: Image.TileVertically
        }

        Image {
            source: "qrc:/resources/L5RRiz/cadre_5.png"
            //scale: 0.8
        }
        Image {
            source: "qrc:/resources/L5RRiz/cadre_6.png"
            //scale: 0.8
            Layout.fillWidth: true
            fillMode: Image.TileHorizontally

        }
        Image {
            source: "qrc:/resources/L5RRiz/cadre_7.png"
//            /scale: 0.8
        }
    }
