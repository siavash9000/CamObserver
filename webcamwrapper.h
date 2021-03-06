#ifndef OPENCVQTCONVERTER_H
#define OPENCVQTCONVERTER_H
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QPixmap>
#include <QDebug>
#include <QThread>
#include "opencv2/imgproc/imgproc.hpp"
#include "speechsynthesizer.h"
#include <boost/circular_buffer.hpp>

namespace camobserver{

class WebCamWrapper: public QObject{
Q_OBJECT

public:
    WebCamWrapper();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
    IplImage* takeWebcamShot();
    void addFaceRectangleToImage();
    void convertToQImage();
    cv::Mat getWebcamAsMat();
    void setFaces(std::vector<cv::Rect_<int> > faces,
                  std::vector<std::string> text,
                  std::vector<cv::Point> facePoints);
private:
    CvCapture* m_camera;
    QImage m_image;
    IplImage *m_openCV_image;
    static int objectCount;
    std::vector<cv::Rect_<int> > m_faces;
    std::vector<std::string> m_text;
    std::vector<cv::Point> m_points;
};

}
#endif // OPENCVQTCONVERTER_H
