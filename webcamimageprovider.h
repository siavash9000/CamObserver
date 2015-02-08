#ifndef WEBCAMIMAGEPROVIDER_H
#define WEBCAMIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include "webcamwrapper.h"

namespace camobserver {

class WebcamImageProvider : public QQuickImageProvider
{
public:
    WebcamImageProvider(WebCamWrapper& webCam);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
private:
    WebCamWrapper& webCamWrapper;

};

}
#endif // WEBCAMIMAGEPROVIDER_H
