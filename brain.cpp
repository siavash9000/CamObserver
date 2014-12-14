#include "brain.h"

Brain::Brain(WebCamWrapper& webcam):m_webcam(webcam)
{
    m_faceDetector.moveToThread(&facedetectorThread);
    QTimer *faceDetectionTimer = new QTimer(this);
    QObject::connect(faceDetectionTimer, SIGNAL(timeout()), this, SLOT(onFacesDetectionUpdate()));
    faceDetectionTimer->start(100);
    QObject::connect(this, SIGNAL(triggerFaceDetection(cv::Mat)),
                     &m_faceDetector, SLOT(detectFaces(cv::Mat)));
    QObject::connect(&m_faceDetector, SIGNAL(faceDetection(std::vector<cv::Rect_<int> > )),
                     this, SLOT(onFacesDetection(std::vector<cv::Rect_<int> > )));
    facedetectorThread.start();
}

void Brain::onFacesDetectionUpdate(){
    qDebug() << "triggered face detection";
    cv::Mat image = m_webcam.getWebcamAsMat();
    emit triggerFaceDetection(image);
}

void Brain::onFacesDetection(std::vector<cv::Rect_<int> > faces){
    m_webcam.setFaces(faces);
}
