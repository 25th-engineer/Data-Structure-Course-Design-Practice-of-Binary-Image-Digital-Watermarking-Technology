#-------------------------------------------------
#
# Project created by QtCreator 2019-02-03T14:45:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageEncodeAdvance
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#INCLUDEPATH += $$PWD/opencv/include
INCLUDEPATH += /usr/local/include \
               /usr/local/include/opencv4 \
               /usr/local/include/opencv4/opencv2

#LIBS += $$PWD/opencv/lib/opencv_world320.lib
LIBS += /usr/local/lib/libopencv_calib3d.so.4.0.1 \
        /usr/local/lib/libopencv_core.so.4.0.1 \
        /usr/local/lib/libopencv_features2d.so.4.0.1 \
        /usr/local/lib/libopencv_flann.so.4.0.1 \
        /usr/local/lib/libopencv_highgui.so.4.0.1 \
        /usr/local/lib/libopencv_imgcodecs.so.4.0.1 \
        /usr/local/lib/libopencv_imgproc.so.4.0.1 \
        /usr/local/lib/libopencv_ml.so.4.0.1 \
        /usr/local/lib/libopencv_objdetect.so.4.0.1 \
        /usr/local/lib/libopencv_photo.so.4.0.1 \
        /usr/local/lib/libopencv_stitching.so.4.0.1 \
        /usr/local/lib/libopencv_videoio.so.4.0.1 \
        /usr/local/lib/libopencv_video.so.4.0.1

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bmputil.cpp \
    addditional_utility.cpp

HEADERS += \
        mainwindow.h \
    bmputil.h \
    addditional_utility.h

FORMS += \
        mainwindow.ui

TARGET = "The Binary BMP Picture watermarking Program"

RC_FILE = my_app.rc
