#ifndef FACEDETECTIONVISUALIZER_H
#define FACEDETECTIONVISUALIZER_H

#include "webcamwrapper.h"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include <opencv/cv.h>
#include <QObject>
#include <QDebug>
#include <QTime>
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "facerecognizer.h"

using namespace std;
using namespace cv;
namespace camobserver {

class FaceDetector: public QObject
{
    Q_OBJECT
public:
    FaceDetector(WebCamWrapper& cam);
public  slots:
    void detectFaces(cv::Mat image);
signals:
    void faceDetection(vector<cv::Rect_<int> > faces, vector<string> visualizationText);
private:
     FaceRecognizer m_recognizer;
     cv::CascadeClassifier m_haar_cascade_frontalface;
     cv::CascadeClassifier m_haar_cascade_alternative;
     WebCamWrapper& m_webCamWrapper;
     std::tuple<vector< cv::Rect_<int> >,vector<prediction>>  detectFaceRectangle(cv::Mat& image);
};
}
#endif // FACEDETECTIONVISUALIZER_H
