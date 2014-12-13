#include <QApplication>
#include <QQmlApplicationEngine>
#include "webcamimageprovider.h"
#include "facerecognizerwrapper.h"
#include "facedetector.h"
Q_DECLARE_METATYPE (std::string)
Q_DECLARE_METATYPE (cv::Mat)
Q_DECLARE_METATYPE (std::vector<cv::Rect_<int> >)

int main(int argc, char *argv[])
{
    qRegisterMetaType<std::vector<cv::Rect_<int> >>("std::vector<cv::Rect_<int> >");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<std::string>("std::string");
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    FaceDetector visualizer;
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
