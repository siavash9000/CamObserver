#ifndef CAMERAFRAMEGRABBER_H
#define CAMERAFRAMEGRABBER_H

// Qt includes
#include <QAbstractVideoSurface>
#include <QList>
#include <QCamera>
#include <QVideoProbe>

class CameraFrameGrabber : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit CameraFrameGrabber(QObject *parent = 0);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;

public slots:
    bool present(const QVideoFrame &frame);

signals:
    void frameAvailable(QImage frame);

private:
    QCamera* m_qcamera;
    QVideoProbe m_Probe;
};

#endif // CAMERAFRAMEGRABBER_H
