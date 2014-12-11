#include <QApplication>
#include <QQmlApplicationEngine>
#include "webcamimageprovider.h"
#include "facerecognizerwrapper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    WebCamWrapper webCamWrapper;
    engine.addImageProvider(QLatin1String("webcamimageprovider"), new WebcamImageProvider(webCamWrapper));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *root = engine.rootObjects().first();
    FaceRecognizerWrapper recognizer(webCamWrapper);
    QObject* trainingButton = root->findChild<QObject*>("trainingButton");
    QObject* predictionButton = root->findChild<QObject*>("predictionButton");
    QObject::connect(trainingButton, SIGNAL(startTraining()),&recognizer, SLOT(startTrainingFromWebcam()));
    QObject::connect(trainingButton, SIGNAL(stopTraining()),&recognizer, SLOT(stopTrainingFromWebcam()));
    QObject::connect(predictionButton, SIGNAL(predict()),&recognizer, SLOT(predictFromWebcam()));

    return app.exec();
}
