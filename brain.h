#ifndef BRAIN_H
#define BRAIN_H
#include <QThread>
#include <QDebug>
#include "facedetector.h"
#include "webcamwrapper.h"
#include "speechsynthesizer.h"
#include <QDate>
using namespace std;

class Brain: public QObject
{
    Q_OBJECT
public:
    Brain(WebCamWrapper& webcam);
    void think();
public slots:
    void onFacesDetection(vector<cv::Rect_<int> > faces,vector<string> text);
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
