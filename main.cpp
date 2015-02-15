#include <QApplication>
#include <QQmlApplicationEngine>
#include "webcamimageprovider.h"
#include "facetracker.h"
#include "brain.h"
Q_DECLARE_METATYPE (std::string)
Q_DECLARE_METATYPE (cv::Mat)
Q_DECLARE_METATYPE (std::vector<cv::Rect_<int> >)

using namespace camobserver;

int main(int argc, char *argv[])
{
    qRegisterMetaType<vector<cv::Rect_<int> >>("vector<cv::Rect_<int> >");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<std::vector<cv::Point>>("std::vector<cv::Point>");
    qRegisterMetaType<vector<string>>("vector<string>");
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    WebCamWrapper webCamWrapper;
    engine.addImageProvider(QLatin1String("webcamimageprovider"), new WebcamImageProvider(webCamWrapper));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    qDebug() << "Starting CamObserver with opencv " << CV_MAJOR_VERSION <<'.'<< CV_MINOR_VERSION;
    Brain brain(webCamWrapper);
    brain.think();
    return app.exec();
}
