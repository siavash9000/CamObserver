import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 800
    height: 480
    title: qsTr("WebCamObserver")

    Image {
        id: camera
        source: "image://webcamimageprovider/yellow"
        cache: false
        function reload() {
            var oldSource = source;
            source = "";
            source = oldSource;
        }
    }

    Timer {
        id: camtimer
        interval: 40; running: true; repeat: true
        onTriggered: camera.reload()
    }

    TextField {
        id: interactionField
        objectName: "interactionField"
        anchors.left: camera.right
        width: 160
        height: 480
        placeholderText: qsTr("Enter name")
    }
}
