#ifndef SOUNDTHREAD_H
#define SOUNDTHREAD_H

#include <QRunnable>
#include <espeak/speak_lib.h>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

class SoundThread  : public QRunnable
{
public:
    SoundThread();
    void run();
};

#endif // SOUNDTHREAD_H
