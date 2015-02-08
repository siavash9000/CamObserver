#include "facedetector.h"
namespace camobserver {

FaceDetector::FaceDetector(WebCamWrapper& cam):m_webCamWrapper(cam),m_recognizer(cam)
{
    m_haar_cascade_frontalface.load("haarcascades/haarcascade_frontalface_alt.xml");
    m_haar_cascade_alternative.load("haarcascades/haarcascade_frontalface_alt_tree.xml");
}

void FaceDetector::detectFaces(cv::Mat image){
    std::tuple<vector< cv::Rect_<int> >,vector<prediction>>  results = detectFaceRectangle(image);
    vector<string> text;
    vector< cv::Rect_<int> > faces = std::get<0>(results);
    vector<prediction> predictions = std::get<1>(results);
    if (predictions.size()==faces.size()){
        for (size_t i=0;i<faces.size();i++){
            std::stringstream ss;
            ss << "user: " << std::to_string(predictions[i].label)
               << ",confidence: " << std::to_string(predictions[i].confidence);
            text.push_back(ss.str());
        }
    }
    else {
        for (size_t i=0;i<faces.size();i++){
            text.push_back("unknown");
        }
    }
    emit faceDetection(faces,text);
}

std::tuple<vector< cv::Rect_<int> >,vector<prediction>> FaceDetector::detectFaceRectangle(cv::Mat& image){
    std::vector<cv::Rect_<int> > faces;
    cv::Mat gray;
    cv::cvtColor(image, gray, CV_BGR2GRAY);
    m_haar_cascade_frontalface.detectMultiScale(gray, faces);
    vector<prediction> predictions;
    if (faces.size()>0){
        if (m_recognizer.m_labels.size()==0){
            m_recognizer.trainFace(faces[0]);
        }
        else{
            predictions = m_recognizer.predictFromWebcam(faces);
        }
    }
    return make_tuple(faces,predictions);
}

}
