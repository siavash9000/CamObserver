#ifndef FACEDETECTIONVISUALIZER_H
#define FACEDETECTIONVISUALIZER_H

#include "webcamwrapper.h"
#include "opencv2/core/core.hpp"
#include "opencv2/face/facerec.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv/cv.h>
#include <QObject>
#include <QDebug>
#include <QTime>
using namespace std;
using namespace cv;
using namespace cv::face;

class FaceDetector: public QObject
{
    Q_OBJECT
public:
    FaceDetector(WebCamWrapper& cam);
    vector<cv::Rect_<int> > detectFaceRectangle(cv::Mat& image);
    void startTrainingFromWebcam();
    void predictFromWebcam();
public  slots:
    void detectFaces(cv::Mat image);
signals:
    void faceDetection(vector<cv::Rect_<int> > faces);
private:
     cv::CascadeClassifier m_haar_cascade_frontalface;
     cv::CascadeClassifier m_haar_cascade_alternative;
     vector<int> m_labels;
     Ptr<face::FaceRecognizer> model;
     WebCamWrapper& webCamWrapper;
};

#endif // FACEDETECTIONVISUALIZER_H
