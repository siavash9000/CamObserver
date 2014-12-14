#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H

#include <QDebug>
#include <QTimer>
#include "webcamwrapper.h"
#include "opencv2/core/core.hpp"
#include "opencv2/face/facerec.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace cv;
using namespace cv::face;
using namespace std;

class FaceRecognizerWrapper : public QObject
{
    Q_OBJECT
public:
    FaceRecognizerWrapper(WebCamWrapper& webCam);
private:
    WebCamWrapper& webCamWrapper;
    vector<Mat> images;
    vector<int> labels;
    QTimer *timer;
    Mat convertIplImageToMatrix(IplImage* iplImage);
    Ptr<FaceRecognizer> model;
    int label;
public
slots:
    void startTrainingFromWebcam();
    void predictFromWebcam();
signals:
    void foundPrediction(std::string prediction);

};

#endif // FACERECOGNIZER_H
