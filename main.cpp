#include <QApplication>
#include <QQmlApplicationEngine>
#include "webcamimageprovider.h"
#include "facerecognizerwrapper.h"
#include "facedetectionvisualizer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    FaceDetectionVisualizer visualizer;
    WebCamWrapper webCamWrapper(visualizer);
    engine.addImageProvider(QLatin1String("webcamimageprovider"), new WebcamImageProvider(webCamWrapper));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *root = engine.rootObjects().first();
    FaceRecognizerWrapper recognizer(webCamWrapper);
    QObject* trainingButton = root->findChild<QObject*>("trainingButton");
    QObject* predictionButton = root->findChild<QObject*>("predictionButton");
    QObject* faceShapeButton = root->findChild<QObject*>("faceShapeButton");
    QObject::connect(trainingButton, SIGNAL(startTraining()),&recognizer, SLOT(startTrainingFromWebcam()));
    QObject::connect(trainingButton, SIGNAL(stopTraining()),&recognizer, SLOT(stopTrainingFromWebcam()));
    QObject::connect(predictionButton, SIGNAL(predict()),&recognizer, SLOT(predictFromWebcam()));
    QObject::connect(faceShapeButton, SIGNAL(toggleVisualization()),&webCamWrapper, SLOT(onToggleVisualization()));



    return app.exec();
}
