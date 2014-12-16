#include <QApplication>
#include <QQmlApplicationEngine>
#include "webcamimageprovider.h"
#include "facedetector.h"
#include "brain.h"
Q_DECLARE_METATYPE (std::string)
Q_DECLARE_METATYPE (cv::Mat)
Q_DECLARE_METATYPE (std::vector<cv::Rect_<int> >)

int main(int argc, char *argv[])
{
    qRegisterMetaType<vector<cv::Rect_<int> >>("vector<cv::Rect_<int> >");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<vector<string>>("vector<string>");
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    WebCamWrapper webCamWrapper;
    engine.addImageProvider(QLatin1String("webcamimageprovider"), new WebcamImageProvider(webCamWrapper));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    Brain brain(webCamWrapper);
    brain.think();
    return app.exec();
}
