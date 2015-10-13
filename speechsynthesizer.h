#ifndef SOUNDTHREAD_H
#define SOUNDTHREAD_H

//#include <espeak/speak_lib.h>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
namespace camobserver {

class SpeechSynthesizer  : public QObject
{
    Q_OBJECT
public:
    SpeechSynthesizer();
public slots:
    void onSay(std::string message);
};

}
#endif // SOUNDTHREAD_H
