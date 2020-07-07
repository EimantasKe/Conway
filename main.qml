import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.15
import Conways 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 600
    height: 500
    minimumWidth: 400
    minimumHeight: 300

    color: "#000000"
    title: qsTr("Game of Life")

    // main view - a table where the Game of Life is running
    TableView {
        id: tableView
        anchors.fill: parent

        rowSpacing: 1
        columnSpacing: 1

        // enable scrolling
        ScrollBar.horizontal: ScrollBar {}
        ScrollBar.vertical: ScrollBar {}

        // create cells
        delegate: Rectangle {
            id: cell
            implicitWidth: 20
            implicitHeight: 20
            required property var model
            required property bool value
            color: value ? "#44a63f" : "#ffffff"

            // allows for switching between live and dead cells
            MouseArea {
                anchors.fill: parent
                onClicked: parent.model.value = !parent.value
            }
        }
        // connect QML with C++
        model: Conway {
            id: conways
        }
        // sets the default view of the board as center
        contentX: (contentWidth - width) / 2;
        contentY: (contentHeight - height) / 2;
    }

    // the controller part of the view
    footer: Rectangle {
        signal nextStep

        id: footer
        height: 40
        color: "#000000"

        RowLayout {
            anchors.centerIn: parent

            // allows changing speed of execution
            SpinBox {
                id: spinbox
                from: 10
                value: 50
                to: 100
                stepSize: 10
                //anchors.centerIn: parent

                property int decimals: 1
                property real realValue: value / 100

                validator: DoubleValidator {
                    bottom: Math.min(spinbox.from, spinbox.to)
                    top:  Math.max(spinbox.from, spinbox.to)
                }

                textFromValue: function(value, locale) {
                    return Number(value / 100).toLocaleString(locale, 'f', spinbox.decimals)
                }

                valueFromText: function(text, locale) {
                    return Number.fromLocaleString(locale, text)*100
                }
            }
            // space between objects
            Item {
                width: 100
            }
            // button for pausing / resuming
            Button {
                text: timer.running ? "Pause" : "Run"
                onClicked: timer.running = !timer.running
            }
        }
        // main timer responsible for running the code
        Timer {
            id: timer
            interval: 1000 - (980 * spinbox.realValue)
            running: false
            repeat: true

            onTriggered: conways.nextStep()
        }
    }
}
