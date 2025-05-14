import QtQuick
import QtQuick.Window
import QtQuick.Controls

Window {
    visible: true
    visibility: Window.FullScreen
    title: "Output on " + screenName

    Rectangle {
        anchors.fill: parent
        color: "#202020"

        Text {
            anchors.centerIn: parent
            font.pixelSize: 48
            color: "white"
            text: "Screen: " + screenName
        }
    }
}
