#include "brain.h"
namespace camobserver {

Brain::Brain(WebCamWrapper& webcam):m_webcam(webcam),m_faceTracker(m_webcam)
{
    m_faceTracker.moveToThread(&facedetectorThread);

    QObject::connect(this, SIGNAL(triggerFaceDetection(cv::Mat)),
                     &m_faceTracker, SLOT(detectFaces(cv::Mat)));
    QObject::connect(&m_faceTracker, SIGNAL(faceDetection(vector<cv::Rect_<int> >,vector<string>,std::vector<cv::Point>)),
                     this, SLOT(onFacesDetection(vector<cv::Rect_<int> >,vector<string>,std::vector<cv::Point>)));
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
    if (m_webcam.newImage()){
    cv::Mat image = m_webcam.getWebcamAsMat();
    emit triggerFaceDetection(image);
    }
}

void Brain::onFacesDetection(vector<cv::Rect_<int> > faces,
                             vector<string> text,
                             std::vector<cv::Point> facePoints){
    m_webcam.setFaces(faces,text,facePoints);
}

void Brain::synthesizeSound()
{
    std::string message("hello user");
    emit say(message);
}

}
