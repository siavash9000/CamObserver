#ifndef BRAIN_H
#define BRAIN_H
#include <QThread>
#include "facedetector.h"
#include <QDebug>
#include "webcamwrapper.h"

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
private:
    WebCamWrapper& m_webcam;
    FaceDetector m_faceDetector;
    QThread facedetectorThread;
};

#endif // BRAIN_H
