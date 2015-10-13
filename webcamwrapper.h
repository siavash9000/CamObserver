#ifndef OPENCVQTCONVERTER_H
#define OPENCVQTCONVERTER_H
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QPixmap>
#include <QDebug>
#include <QThread>
#include "opencv2/imgproc/imgproc.hpp"
#include "speechsynthesizer.h"
#include <QCamera>
//#include <boost/circular_buffer.hpp>

namespace camobserver{

class WebCamWrapper: public QObject{
Q_OBJECT

public Q_SLOTS:
    void takeWebcamShot(QImage image);
public:
    WebCamWrapper();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

    void addFaceRectangleToImage();
    void convertToQImage();
    void convertToCvImage();
    cv::Mat getWebcamAsMat();
    void setFaces(std::vector<cv::Rect_<int> > faces,
                  std::vector<std::string> text,
                  std::vector<cv::Point> facePoints);
    bool newImage();
private:
    QCamera* m_qcamera;
    QImage m_image;
    bool m_newImage;
    IplImage *m_openCV_image;
    static int objectCount;
    std::vector<cv::Rect_<int> > m_faces;
    std::vector<std::string> m_text;
    std::vector<cv::Point> m_points;
};

}
#endif // OPENCVQTCONVERTER_H
