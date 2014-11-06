#include <QApplication>
#include <QQmlApplicationEngine>
#include "webcamimageprovider.h"
#include "facerecognizer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("webcamimageprovider"), new WebcamImageProvider());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject *root = engine.rootObjects().first();
    FaceRecognizer recognizer;
    QObject* button = root->findChild<QObject*>("trainingButton");
    QObject::connect(button, SIGNAL(startTraining()),&recognizer, SLOT(startTrainingFromWebcam()));
    QObject::connect(button, SIGNAL(stopTraining()),&recognizer, SLOT(stopTrainingFromWebcam()));

    return app.exec();
}
