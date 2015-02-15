TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    webcamimageprovider.cpp \
    webcamwrapper.cpp \
    speechsynthesizer.cpp \
    brain.cpp \
    facerecognizer.cpp \
    facetracker.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    webcamimageprovider.h \
    webcamwrapper.h \
    speechsynthesizer.h \
    brain.h \
    facerecognizer.h \
    facetracker.h

CONFIG += c++11

CONFIG += link_pkgconfig
PKGCONFIG += opencv

LIBS += -L$ESPEAK_HOME -lespeak
LIBS += \
       -lboost_system\
