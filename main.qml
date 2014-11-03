import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 800
    height: 480
    title: qsTr("WebCamObserver")

    Image {
        id: camera
        width: 500
        height: 480
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

    Button {
        x: 700
        y: 20
        width: 80
        height: 80
        text: "Start/Stop"
        onClicked:
            if (camtimer.running)
                camtimer.stop()
            else
                camtimer.start()
    }
}
