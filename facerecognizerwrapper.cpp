#include "facerecognizerwrapper.h"

FaceRecognizerWrapper::FaceRecognizerWrapper(WebCamWrapper& webCam):webCamWrapper(webCam)
{}

void FaceRecognizerWrapper::startTrainingFromWebcam() {
    qDebug() << "Starting the training with opencv " << CV_MAJOR_VERSION <<'.'<< CV_MINOR_VERSION;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(doTraining()));
    timer->start(500);
    Ptr<FaceRecognizer> model =  createEigenFaceRecognizer();
    Mat mat = convertIplImageToMatrix(webCamWrapper.takeWebcamShot());
    vector<Mat> images;
    vector<int> labels;
    images.push_back(mat);
    labels.push_back(0);
    model->train(images, labels);
}

cv::Mat FaceRecognizerWrapper::convertIplImageToMatrix(IplImage* iplImage)
{
    return cv::cvarrToMat(iplImage);
}

void FaceRecognizerWrapper::doTraining(){
    qDebug() << "training iteration";
    Mat mat = convertIplImageToMatrix(webCamWrapper.takeWebcamShot());
    vector<Mat> images;
    vector<int> labels;
    images.push_back(mat);
    labels.push_back(0);
}

void FaceRecognizerWrapper::stopTrainingFromWebcam() {
    qDebug() << "Stoping the training";
    timer->stop();
}

void FaceRecognizerWrapper::predictFromWebcam() {
    qDebug() << "Trying to predict face from current webcam";
}

