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

    Button {
        id: trainingButton
        objectName: "trainingButton"
        anchors.left: camera.right
        property var isCurrentlyTraining: false
        width: 100
        height: 100
        text: "Start Training"
        signal startTraining()
        signal stopTraining()
        onClicked:
            if (isCurrentlyTraining){
                trainingButton.text="Stop Training"
                trainingButton.stopTraining()
                isCurrentlyTraining=false
            }
            else {
                trainingButton.text="Start Training"
                trainingButton.startTraining()
                isCurrentlyTraining=true
            }
    }

    Button {
        id: predictionButton
        objectName: "predictionButton"
        anchors.left: camera.right
        anchors.top: trainingButton.bottom
        width: 100
        height: 100
        text: "Predict"
        signal predict()
        onClicked:
            predictionButton.predict()
    }
}
