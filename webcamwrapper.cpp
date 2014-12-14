#include "webcamwrapper.h"

int WebCamWrapper::objectCount = 0;

WebCamWrapper::WebCamWrapper()
{
    m_camera = cvCaptureFromCAM(CV_CAP_ANY);
    assert(m_camera);
    m_openCV_image = cvQueryFrame(m_camera);
    assert(m_openCV_image);
    objectCount++;
}

IplImage* WebCamWrapper::takeWebcamShot()
{
    m_openCV_image = cvQueryFrame(m_camera);
    return m_openCV_image;
}

cv::Mat WebCamWrapper::getWebcamAsMat(){
    cv::Mat image = cv::cvarrToMat(m_openCV_image);
    return image;
}
void WebCamWrapper::setFaces(std::vector<cv::Rect_<int> > faces){
    m_faces = faces;
}

void WebCamWrapper::addFaceRectangleToImage()
{
    cv::Mat image = getWebcamAsMat();
    for(int i = 0; i < m_faces.size(); i++) {
        cv::Rect face_i = m_faces[i];
        cv::rectangle(image, face_i, CV_RGB(0, 255,0), 1);
    }
    m_openCV_image = new IplImage(image);
}

void WebCamWrapper::convertToQImage()
{
    int cvIndex, cvLineStart;

    switch (m_openCV_image->depth) {
    case IPL_DEPTH_8U:
        switch (m_openCV_image->nChannels) {
        case 3:
            if ( (m_openCV_image->width != m_image.width()) || (m_openCV_image->height != m_image.height()) ) {
                QImage temp(m_openCV_image->width, m_openCV_image->height, QImage::Format_RGB32);
                m_image = temp;
            }
            cvIndex = 0; cvLineStart = 0;
            for (int y = 0; y < m_openCV_image->height; y++) {
                unsigned char red,green,blue;
                cvIndex = cvLineStart;
                for (int x = 0; x < m_openCV_image->width; x++) {
                    red = m_openCV_image->imageData[cvIndex+2];
                    green = m_openCV_image->imageData[cvIndex+1];
                    blue = m_openCV_image->imageData[cvIndex+0];

                    m_image.setPixel(x,y,qRgb(red, green, blue));
                    cvIndex += 3;
                }
                cvLineStart += m_openCV_image->widthStep;
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
}

QPixmap WebCamWrapper::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    takeWebcamShot();
    addFaceRectangleToImage();
    convertToQImage();
    return QPixmap::fromImage(m_image);
}
