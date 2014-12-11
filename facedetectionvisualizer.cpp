#include "facedetectionvisualizer.h"

FaceDetectionVisualizer::FaceDetectionVisualizer()
{
}

std::vector< cv::Rect_<int> > FaceDetectionVisualizer::detectFaceRectangle(cv::Mat& image){
    cv::CascadeClassifier haar_cascade;
    haar_cascade.load("haarcascades/haarcascade_frontalface_default.xml");
    std::vector<cv::Rect_<int> > faces;
    cv::Mat gray;
    cv::cvtColor(image, gray, CV_BGR2GRAY);
    haar_cascade.detectMultiScale(gray, faces);
    return faces;
}
