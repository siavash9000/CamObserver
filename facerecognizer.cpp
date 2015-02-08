#include "facerecognizer.h"
namespace camobserver{

FaceRecognizer::FaceRecognizer(WebCamWrapper& cam):m_webCamWrapper(cam)
{
    model =  createLBPHFaceRecognizer();
}

FaceRecognizer::~FaceRecognizer()
{

}

void FaceRecognizer::trainFace(cv::Rect_<int> faceRectangle ) {
    Mat mat = m_webCamWrapper.getWebcamAsMat();
    Mat gray;
    cv::cvtColor(mat, gray, CV_BGR2GRAY);
    Mat face = gray(faceRectangle);
    m_images.push_back(face);
    m_labels.push_back(m_labels.size()+1);
    if (m_labels.size()==1){
        model->train(m_images, m_labels);
    }
    else {
        model->update(m_images, m_labels);
    }
}

vector<prediction> FaceRecognizer::predictFromWebcam(vector<cv::Rect_<int> > faces) {
    Mat mat = m_webCamWrapper.getWebcamAsMat();
    Mat gray;
    cv::cvtColor(mat, gray, CV_BGR2GRAY);
    vector<prediction> result;
    for (cv::Rect_<int> current: faces){
        Mat face = gray(current);
        int label;
        double confidence;
        model->predict(face,label,confidence);
        prediction pred;
        pred.label = label;
        pred.confidence = confidence;
        result.push_back(pred);
    }
    return result;
}

}
