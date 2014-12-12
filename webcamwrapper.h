#ifndef OPENCVQTCONVERTER_H
#define OPENCVQTCONVERTER_H
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QPixmap>
#include <QDebug>
#include "facedetectionvisualizer.h"
#include "speechsynthesizer.h"
#include <QThreadPool>


class WebCamWrapper: public QObject{
Q_OBJECT

public:
    WebCamWrapper(FaceDetectionVisualizer visualizer);
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    IplImage* takeWebcamShot();
    void addFaceRectangleToImage(std::vector<cv::Rect_<int> > faces,cv::Mat image);
    void convertToQImage();
    void synthesizeSound();
public slots:
    void onToggleVisualization();
signals:
    void say(std::string message);
private:
    CvCapture* m_camera;
    QImage m_image;
    IplImage *m_openCV_image;
    static int objectCount;
    FaceDetectionVisualizer m_visualizer;
    clock_t lastFaceShapeDetection;
    std::vector<cv::Rect_<int> > faces;
    bool visualizeFaceShapes;
    SpeechSynthesizer speech;
    QThread soundThread;
};

#endif // OPENCVQTCONVERTER_H
