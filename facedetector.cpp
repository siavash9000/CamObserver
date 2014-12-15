#include "facedetector.h"
FaceDetector::FaceDetector(WebCamWrapper& cam):webCamWrapper(cam)
{
    m_haar_cascade_frontalface.load("haarcascades/haarcascade_frontalface_alt.xml");
    m_haar_cascade_alternative.load("haarcascades/haarcascade_frontalface_alt_tree.xml");
}

void FaceDetector::detectFaces(cv::Mat image){
    std::vector< cv::Rect_<int> > faces = detectFaceRectangle(image);
    emit faceDetection(faces);
}

std::vector< cv::Rect_<int> > FaceDetector::detectFaceRectangle(cv::Mat& image){
    std::vector<cv::Rect_<int> > faces;
    cv::Mat gray;
    cv::cvtColor(image, gray, CV_BGR2GRAY);
    m_haar_cascade_frontalface.detectMultiScale(gray, faces);
    if (faces.size()==0){
        m_haar_cascade_alternative.detectMultiScale(gray, faces);
    }
    return faces;
}

void FaceDetector::startTrainingFromWebcam() {
    qDebug() << "Starting the training with opencv " << CV_MAJOR_VERSION <<'.'<< CV_MINOR_VERSION;
    model =  createLBPHFaceRecognizer();
    Mat mat = webCamWrapper.getWebcamAsMat();
    cv::CascadeClassifier haar_cascade;
    haar_cascade.load("haarcascades/haarcascade_frontalface_default.xml");
    std::vector<cv::Rect_<int> > faces;
    Mat gray;
    cv::cvtColor(mat, gray, CV_BGR2GRAY);
    haar_cascade.detectMultiScale(gray, faces);
    Mat face = gray(faces[0]);
    vector<Mat> images;
    vector<int> labels;
    images.push_back(face);
    m_labels.push_back(0);
    model->train(images, labels);
}

void FaceDetector::predictFromWebcam() {
    qDebug() << "Trying to predict face from current webcam";
    Mat mat = webCamWrapper.getWebcamAsMat();
    cv::CascadeClassifier haar_cascade;
    haar_cascade.load("haarcascades/haarcascade_frontalface_default.xml");
    std::vector<cv::Rect_<int> > faces;
    Mat gray;
    cv::cvtColor(mat, gray, CV_BGR2GRAY);
    haar_cascade.detectMultiScale(gray, faces);
    Mat face = gray(faces[0]);
    int prediction = model->predict(face);
    qDebug() << "Prediction:";
    qDebug() << prediction;
}
