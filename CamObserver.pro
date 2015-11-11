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

linux:!android {
    # using pkg-config
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
    LIBS += -L$ESPEAK_HOME -lespeak -lboost_system
}


android {
    # full path to OpenCV Android SDK
    OPENCV_PATH = /home/siavash/Android/OpenCV-android-sdk

    INCLUDEPATH += $${OPENCV_PATH}/sdk/native/jni/include/

    LIBS += -L$${OPENCV_PATH}/sdk/native/libs/armeabi-v7a/ \
            -lopencv_calib3d \
            -lopencv_contrib \
            -lopencv_features2d \
            -lopencv_flann \
            -lopencv_highgui \
            -lopencv_androidcamera \
            -lopencv_objdetect \
            -lopencv_imgproc \
            -lopencv_core \
            -lopencv_legacy \
            -lopencv_ml \
            -lopencv_photo \
            -lopencv_stitching \
            -lopencv_ts \
            -lopencv_video \
            -lopencv_videostab

    LIBS += -L$${OPENCV_PATH}/sdk/native/3rdparty/libs/armeabi-v7a \
            -lIlmImf \
            -llibjasper \
            -llibjpeg \
            -llibpng \
            -llibtiff \
            -ltbb
}



