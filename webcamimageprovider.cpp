#include "webcamimageprovider.h"

WebcamImageProvider::WebcamImageProvider(WebCamWrapper& webCam)
    : QQuickImageProvider(QQuickImageProvider::Pixmap),webCamWrapper(webCam)
{}

QPixmap WebcamImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
   return webCamWrapper.requestPixmap(id,size,requestedSize);
}
