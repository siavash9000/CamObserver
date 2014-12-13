#include "facedetector.h"

FaceDetector::FaceDetector()
{

}

void FaceDetector::detectFaces(cv::Mat image){
    std::vector< cv::Rect_<int> > faces = detectFaceRectangle(image);
    emit faceDetection(faces);
}

std::vector< cv::Rect_<int> > FaceDetector::detectFaceRectangle(cv::Mat& image){
    cv::CascadeClassifier haar_cascade;
    haar_cascade.load("haarcascades/haarcascade_frontalface_alt.xml");
    std::vector<cv::Rect_<int> > faces;
    cv::Mat gray;
    cv::cvtColor(image, gray, CV_BGR2GRAY);
    haar_cascade.detectMultiScale(gray, faces);
    return faces;
}
