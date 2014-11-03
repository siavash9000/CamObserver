#ifndef WEBCAMIMAGEPROVIDER_H
#define WEBCAMIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QPixmap>
#include <QDebug>
#include <opencv/cv.h>

class WebcamImageProvider : public QQuickImageProvider
{
public:
    WebcamImageProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
private:
    CvCapture* m_camera;
    QImage m_image;
};
#endif // WEBCAMIMAGEPROVIDER_H
