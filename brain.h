#ifndef BRAIN_H
#define BRAIN_H
#include <QThread>
#include <QDebug>
#include "facedetector.h"
#include "webcamwrapper.h"
#include "speechsynthesizer.h"

class Brain: public QObject
{
    Q_OBJECT
public:
    Brain(WebCamWrapper& webcam);
public slots:
    void onFacesDetection(std::vector<cv::Rect_<int> > faces);
    void onFacesDetectionUpdate();
signals:
    void triggerFaceDetection(cv::Mat image);
    void say(std::string message);
private:
    void synthesizeSound();
    WebCamWrapper& m_webcam;
    FaceDetector m_faceDetector;
    QThread facedetectorThread;
    SpeechSynthesizer speech;
    QThread soundThread;
};

#endif // BRAIN_H
