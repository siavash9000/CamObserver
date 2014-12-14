#ifndef OPENCVQTCONVERTER_H
#define OPENCVQTCONVERTER_H
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QPixmap>
#include <QDebug>
#include "facedetector.h"
#include "speechsynthesizer.h"
#include <QThread>


class WebCamWrapper: public QObject{
Q_OBJECT

public:
    WebCamWrapper();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    IplImage* takeWebcamShot();
    void addFaceRectangleToImage(std::vector<cv::Rect_<int> > faces);
    void convertToQImage();
    void synthesizeSound();
    cv::Mat getWebcamAsMat();
    void setFaces(std::vector<cv::Rect_<int> > faces);
public slots:
    void onToggleVisualization();
signals:
    void say(std::string message);
    void triggerFaceDetection(cv::Mat image);
private:
    CvCapture* m_camera;
    QImage m_image;
    IplImage *m_openCV_image;
    static int objectCount;
    clock_t lastFaceShapeDetection;
    std::vector<cv::Rect_<int> > m_faces;
    bool visualizeFaceShapes;
    SpeechSynthesizer speech;
    QThread soundThread;
};

#endif // OPENCVQTCONVERTER_H
