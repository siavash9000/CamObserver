import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 800
    height: 800
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
}
