#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H

#include "webcamwrapper.h"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
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

using namespace std;
using namespace cv;

struct prediction {
  int   label;
  double confidence;
};

namespace camobserver{

class FaceRecognizer
{
public:
    FaceRecognizer(WebCamWrapper& cam);
    ~FaceRecognizer();
    void trainFace(cv::Rect_<int> face);
    vector<prediction> predictFromWebcam(vector<cv::Rect_<int> > faces);
    vector<Mat> m_images;
    vector<int> m_labels;
    Ptr<cv::FaceRecognizer> model;
    WebCamWrapper& m_webCamWrapper;
};

}

#endif // FACERECOGNIZER_H
