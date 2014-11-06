#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H

#include <QDebug>
class FaceRecognizer : public QObject
{
    Q_OBJECT
public:
    FaceRecognizer();

public slots:
    void startTrainingFromWebcam();
    void stopTrainingFromWebcam();
};

#endif // FACERECOGNIZER_H
