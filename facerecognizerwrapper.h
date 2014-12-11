#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H

#include <QDebug>
#include <QTimer>
#include "webcamwrapper.h"
#include "opencv2/core/core.hpp"
#include "opencv2/face/facerec.hpp"
#include "opencv2/highgui.hpp"

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
public slots:
    void doTraining();
    void startTrainingFromWebcam();
    void stopTrainingFromWebcam();
    void predictFromWebcam();
};

#endif // FACERECOGNIZER_H
