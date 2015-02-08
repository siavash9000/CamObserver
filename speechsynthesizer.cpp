#include "speechsynthesizer.h"
namespace camobserver {

SpeechSynthesizer::SpeechSynthesizer()
{
    qDebug() << "SpeechSynthesizer created";
    espeak_Initialize(
      AUDIO_OUTPUT_PLAYBACK, // plays audio data asynchronously
      500,                   // length of buffers for synth function, in ms
      nullptr,               // dir containing espeak-data, or null for default
      0);                    // options are mostly for phoneme callbacks, so 0

}

void SpeechSynthesizer::onSay(std::string message)
{
    qDebug() << "onSay triggered";
    QEventLoop loop;
    QTimer::singleShot(2500, &loop, SLOT(quit()));
    loop.exec();

    espeak_ERROR err = espeak_Synth(
      message.c_str(),   // text
      message.size(),    // size
      0,                 // position to start from
      POS_CHARACTER,     // whether above 0 pos is chars/word/sentences
      message.size(),    // end position, 0 indicating no end
      espeakCHARS_AUTO | // flags: AUTO      8 bit or UTF8 automatically
      espeakENDPAUSE,    //        ENDPAUSE  sentence pause at end of text
      nullptr,           // message identifier given to callback (unused)
      nullptr);          // user data, passed to the callback function (unused)

    if (err != EE_OK)
      qDebug() << "Error synthesising speech" << endl;

    // Wait until everything has been spoken
    espeak_Synchronize();
}

}
