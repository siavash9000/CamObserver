#ifndef FACEDETECTIONVISUALIZER_H
#define FACEDETECTIONVISUALIZER_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/face/facerec.hpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QTimer>

class FaceDetector: public QObject
{
    Q_OBJECT
public:
    FaceDetector();
    std::vector<cv::Rect_<int> > detectFaceRectangle(cv::Mat& image);
public  slots:
    void detectFaces(cv::Mat image);
signals:
    void faceDetection(std::vector<cv::Rect_<int> > faces);
private:

};

#endif // FACEDETECTIONVISUALIZER_H
