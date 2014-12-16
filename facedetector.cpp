#include "facedetector.h"
FaceDetector::FaceDetector(WebCamWrapper& cam):webCamWrapper(cam)
{
    m_haar_cascade_frontalface.load("haarcascades/haarcascade_frontalface_alt.xml");
    m_haar_cascade_alternative.load("haarcascades/haarcascade_frontalface_alt_tree.xml");
    model =  createLBPHFaceRecognizer();
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
    if (m_labels.size()==0){
        trainFace(faces);
    }
    else{
        predictions = predictFromWebcam(faces);
    }
    return make_tuple(faces,predictions);
}

void FaceDetector::trainFace(vector<cv::Rect_<int> > faces) {
    qDebug() << "Starting the training with opencv " << CV_MAJOR_VERSION <<'.'<< CV_MINOR_VERSION;
    Mat mat = webCamWrapper.getWebcamAsMat();
    Mat gray;
    cv::cvtColor(mat, gray, CV_BGR2GRAY);
    for (cv::Rect_<int> current: faces){
        Mat face = gray(current);
        vector<Mat> images;
        images.push_back(face);
        m_labels.push_back(m_labels.size()+1);
        if (m_labels.size()==1){
            model->train(images, m_labels);
        }
        else {
            model->update(images, m_labels);
        }
    }
}

vector<prediction> FaceDetector::predictFromWebcam(vector<cv::Rect_<int> > faces) {
    Mat mat = webCamWrapper.getWebcamAsMat();
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
