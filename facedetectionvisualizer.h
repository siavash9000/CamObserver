#ifndef FACEDETECTIONVISUALIZER_H
#define FACEDETECTIONVISUALIZER_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/face/facerec.hpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>
class FaceDetectionVisualizer
{
public:
    FaceDetectionVisualizer();
    std::vector<cv::Rect_<int> > detectFaceRectangle(cv::Mat& image);
};

#endif // FACEDETECTIONVISUALIZER_H
