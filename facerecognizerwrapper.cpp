#include "facerecognizerwrapper.h"

FaceRecognizerWrapper::FaceRecognizerWrapper(WebCamWrapper& webCam):webCamWrapper(webCam)
{
    label = 0;
}

void FaceRecognizerWrapper::startTrainingFromWebcam() {
    qDebug() << "Starting the training with opencv " << CV_MAJOR_VERSION <<'.'<< CV_MINOR_VERSION;
    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(doTraining()));
    //timer->start(500);
    model =  createLBPHFaceRecognizer();
    Mat mat = convertIplImageToMatrix(webCamWrapper.takeWebcamShot());
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
    labels.push_back(label);
    std::stringstream ss;
    ss << "face" << label << ".jpg";
    imwrite(ss.str(), face );
    label++;
    model->train(images, labels);

}

cv::Mat FaceRecognizerWrapper::convertIplImageToMatrix(IplImage* iplImage)
{
    return cv::cvarrToMat(iplImage);
}

void FaceRecognizerWrapper::predictFromWebcam() {
    qDebug() << "Trying to predict face from current webcam";
    Mat mat = convertIplImageToMatrix(webCamWrapper.takeWebcamShot());
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
    qDebug() << "Prediction:";
}
