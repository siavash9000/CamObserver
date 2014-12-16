#include "brain.h"

Brain::Brain(WebCamWrapper& webcam):m_webcam(webcam),m_faceDetector(m_webcam)
{
    m_faceDetector.moveToThread(&facedetectorThread);

    QObject::connect(this, SIGNAL(triggerFaceDetection(cv::Mat)),
                     &m_faceDetector, SLOT(detectFaces(cv::Mat)));
    QObject::connect(&m_faceDetector, SIGNAL(faceDetection(vector<cv::Rect_<int> >,vector<string>)),
                     this, SLOT(onFacesDetection(vector<cv::Rect_<int> >,vector<string>)));
    speech.moveToThread(&soundThread);
    QObject::connect(this, SIGNAL(say(std::string)),&speech, SLOT(onSay(std::string)));
    synthesizeSound();
}
void Brain::think() {
    facedetectorThread.start();
    soundThread.start();
    QTimer *faceDetectionTimer = new QTimer(this);
    QObject::connect(faceDetectionTimer, SIGNAL(timeout()), this, SLOT(onFacesDetectionUpdate()));
    faceDetectionTimer->start(100);
}

void Brain::onFacesDetectionUpdate(){
    cv::Mat image = m_webcam.getWebcamAsMat();
    emit triggerFaceDetection(image);
}

void Brain::onFacesDetection(vector<cv::Rect_<int> > faces,vector<string> text){
    m_webcam.setFaces(faces,text);
}

void Brain::synthesizeSound()
{
    std::string message("hello user");
    emit say(message);
}
