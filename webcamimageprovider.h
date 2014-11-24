#ifndef WEBCAMIMAGEPROVIDER_H
#define WEBCAMIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include "opencvqtconverter.h"

class WebcamImageProvider : public QQuickImageProvider
{
public:
    WebcamImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
private:
    OpenCVQTConverter converter;

};
#endif // WEBCAMIMAGEPROVIDER_H
