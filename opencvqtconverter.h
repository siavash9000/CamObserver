#ifndef OPENCVQTCONVERTER_H
#define OPENCVQTCONVERTER_H
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QPixmap>
#include <QDebug>
#include <opencv/cv.h>

class OpenCVQTConverter
{
public:
    OpenCVQTConverter();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
private:
    CvCapture* m_camera;
    QImage m_image;
    static int objectCount;
};

#endif // OPENCVQTCONVERTER_H
