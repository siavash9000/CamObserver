#include <QApplication>
#include <QQmlApplicationEngine>
#include "webcamimageprovider.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImageProvider(QLatin1String("webcamimageprovider"), new WebcamImageProvider());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
