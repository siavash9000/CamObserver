TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    webcamimageprovider.cpp \
    webcamwrapper.cpp \
    facerecognizerwrapper.cpp \
    speechsynthesizer.cpp \
    facedetector.cpp \
    brain.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    webcamimageprovider.h \
    webcamwrapper.h \
    facerecognizerwrapper.h \
    speechsynthesizer.h \
    facedetector.h \
    brain.h

CONFIG += c++11

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

LIBS += -L$ESPEAK_HOME -lespeak
