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
    WebCamWrapper(FaceDetector& visualizer);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    IplImage* takeWebcamShot();
    void addFaceRectangleToImage(std::vector<cv::Rect_<int> > faces,cv::Mat image);
    void convertToQImage();
    void synthesizeSound();
public slots:
    void onToggleVisualization();
    void onFacesDetection(std::vector<cv::Rect_<int> > faces);
signals:
    void say(std::string message);
    void triggerFaceDetection(cv::Mat image);
private:
    CvCapture* m_camera;
    QImage m_image;
    IplImage *m_openCV_image;
    static int objectCount;
    FaceDetector& m_visualizer;
    clock_t lastFaceShapeDetection;
    std::vector<cv::Rect_<int> > m_faces;
    bool visualizeFaceShapes;
    SpeechSynthesizer speech;
    QThread soundThread;
    QThread facedetectorThread;
};

#endif // OPENCVQTCONVERTER_H
