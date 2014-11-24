#include "webcamimageprovider.h"

WebcamImageProvider::WebcamImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

QPixmap WebcamImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
   return converter.requestPixmap(id,size,requestedSize);
}
