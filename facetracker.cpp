#include "facetracker.h"
namespace camobserver {

FaceTracker::FaceTracker(WebCamWrapper& cam):m_webCamWrapper(cam),m_recognizer(cam)
{
    m_haar_cascade_frontalface.load("haarcascades/haarcascade_frontalface_alt.xml");
    m_haar_cascade_alternative.load("haarcascades/haarcascade_frontalface_alt_tree.xml");
}

void FaceTracker::detectFaces(cv::Mat image){
    vector< cv::Rect_<int> > faces = detectFaceRectangle(image);
    if (faces.size()>0){
        cv::Point position;
        position.x = faces[0].x + faces[0].width/2;
        position.y = faces[0].y + faces[0].height/2;
        this->facePositions.push_back(position);
    }
    vector<string> text;
    emit faceDetection(faces,text,facePositions);
}

vector< cv::Rect_<int> > FaceTracker::detectFaceRectangle(cv::Mat& image){
    std::vector<cv::Rect_<int> > faces;
    cv::Mat gray;
    cv::cvtColor(image, gray, CV_BGR2GRAY);
    m_haar_cascade_frontalface.detectMultiScale(gray, faces);
    return faces;
}

}
