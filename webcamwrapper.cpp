#include "webcamwrapper.h"
int WebCamWrapper::objectCount = 0;

WebCamWrapper::WebCamWrapper(FaceDetectionVisualizer visualizer)
{
    visualizeFaceShapes = false;
    m_camera = cvCaptureFromCAM(CV_CAP_ANY);
    assert(m_camera);
    m_openCV_image = cvQueryFrame(m_camera);
    assert(m_openCV_image);
    m_visualizer = visualizer;
    lastFaceShapeDetection = clock();
    objectCount++;
    speech.moveToThread(&soundThread);
    QObject::connect(this, SIGNAL(say(std::string)),&speech, SLOT(onSay(std::string)));
    soundThread.start();
}

IplImage* WebCamWrapper::takeWebcamShot()
{
    m_openCV_image = cvQueryFrame(m_camera);
    return m_openCV_image;
}

void WebCamWrapper::addFaceRectangleToImage(std::vector<cv::Rect_<int> > faces,cv::Mat image)
{
    for(int i = 0; i < faces.size(); i++) {
        cv::Rect face_i = faces[i];
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
    clock_t now = clock();
    double diff = double(now - lastFaceShapeDetection) / CLOCKS_PER_SEC;

    cv::Mat image = cv::cvarrToMat(m_openCV_image);
    if (visualizeFaceShapes && diff>0.1) {
        faces = m_visualizer.detectFaceRectangle(image);
        lastFaceShapeDetection = clock();
    }
    addFaceRectangleToImage(faces,image);

    convertToQImage();

    return QPixmap::fromImage(m_image);
}

void WebCamWrapper::synthesizeSound()
{
    std::string message("Hello sia");
    say(message);
}

void WebCamWrapper::onToggleVisualization(){
    qDebug() << "toggled visualization";
    visualizeFaceShapes = !visualizeFaceShapes;
    synthesizeSound();
}
