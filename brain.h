#ifndef BRAIN_H
#define BRAIN_H
#include <QThread>
#include <QDebug>
#include "facetracker.h"
#include "webcamwrapper.h"
#include "speechsynthesizer.h"
#include <QDate>
using namespace std;
namespace camobserver{

class Brain: public QObject
{
    Q_OBJECT
public:
    Brain(WebCamWrapper& webcam);
    void think();
public slots:
    void onFacesDetection(vector<cv::Rect_<int> > faces,vector<string> text,std::vector<cv::Point> facePoints);
    void onFacesDetectionUpdate();
signals:
    void triggerFaceDetection(cv::Mat image);
    void say(std::string message);
private:
    void synthesizeSound();
    WebCamWrapper& m_webcam;
    FaceTracker m_faceTracker;
    QThread facedetectorThread;
    SpeechSynthesizer speech;
    QThread soundThread;
};
}
#endif // BRAIN_H
