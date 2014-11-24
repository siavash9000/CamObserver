#include "opencvqtconverter.h"
int OpenCVQTConverter::objectCount = 0;

OpenCVQTConverter::OpenCVQTConverter()
{
    m_camera = cvCaptureFromCAM(CV_CAP_ANY);
    assert(m_camera);
    IplImage *image = cvQueryFrame(m_camera);
    assert(image);
    objectCount++;
}

QPixmap OpenCVQTConverter::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    IplImage *cvimage = cvQueryFrame(m_camera);
    int cvIndex, cvLineStart;

    switch (cvimage->depth) {
    case IPL_DEPTH_8U:
        switch (cvimage->nChannels) {
        case 3:
            if ( (cvimage->width != m_image.width()) || (cvimage->height != m_image.height()) ) {
                QImage temp(cvimage->width, cvimage->height, QImage::Format_RGB32);
                m_image = temp;
            }
            cvIndex = 0; cvLineStart = 0;
            for (int y = 0; y < cvimage->height; y++) {
                unsigned char red,green,blue;
                cvIndex = cvLineStart;
                for (int x = 0; x < cvimage->width; x++) {
                    red = cvimage->imageData[cvIndex+2];
                    green = cvimage->imageData[cvIndex+1];
                    blue = cvimage->imageData[cvIndex+0];

                    m_image.setPixel(x,y,qRgb(red, green, blue));
                    cvIndex += 3;
                }
                cvLineStart += cvimage->widthStep;
            }
            break;
        default:
            qWarning("This number of channels is not supported\n");
            break;
        }
        break;
    default:
        qWarning("This type of IplImage is not implemented in QOpenCVWidget\n");
        break;
    }

    return QPixmap::fromImage(m_image);
}
