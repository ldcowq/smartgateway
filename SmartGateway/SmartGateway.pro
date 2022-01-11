#-------------------------------------------------
#
# Project created by QtCreator 2021-07-17T02:23:52
#
#-------------------------------------------------

QT += core gui
QT += multimedia
QT += multimediawidgets
QT += network
QT += serialport
QT += charts
QT += mqtt
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = SmartGateway
TEMPLATE = app


SOURCES += main.cpp\
        smartgateway.cpp \
    slidepage/slidepage.cpp \
    app/app.cpp \
    app2/app2.cpp \
    album/album.cpp \
    tools/filetools.cpp \
    video/video.cpp \
    music/music.cpp \
    tools/switchbutton.cpp \
    environment/environment.cpp \
    environment/getsensordatabyserial.cpp \
    homecontrol/homecontrol.cpp \
    camera/camera.cpp \
    weather/weatherinfo.cpp \
    video/customslider.cpp

HEADERS  += smartgateway.h \
    slidepage/slidepage.h \
    app/app.h \
    app2/app2.h \
    album/album.h \
    tools/filetools.h \
    video/video.h \
    music/music.h \
    tools/switchbutton.h \
    environment/environment.h \
    environment/getsensordatabyserial.h \
    homecontrol/homecontrol.h \
    camera/camera.h \
    weather/weatherinfo.h \
    video/customslider.h

RESOURCES += \
    res.qrc

DISTFILES +=

SUBDIRS += \
    appdemo/appdemo.pro

unix:!macx: LIBS += -L$$PWD/../../../../3rdLib/qtmqtt/lib/ -lQt5Mqtt

INCLUDEPATH += $$PWD/../../../../3rdLib/qtmqtt/include
DEPENDPATH += $$PWD/../../../../3rdLib/qtmqtt/include

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_calib3d.so.3.4 \
        /usr/local/lib/libopencv_core.so.3.4 \
        /usr/local/lib/libopencv_features2d.so.3.4 \
        /usr/local/lib/libopencv_highgui.so.3.4 \
        /usr/local/lib/libopencv_imgcodecs.so.3.4 \
        /usr/local/lib/libopencv_imgproc.so.3.4 \
        /usr/local/lib/libopencv_ml.so.3.4 \
        /usr/local/lib/libopencv_objdetect.so.3.4 \
        /usr/local/lib/libopencv_photo.so.3.4 \
        /usr/local/lib/libopencv_stitching.so.3.4 \
        /usr/local/lib/libopencv_video.so.3.4 \

/usr/local/lib/libopencv_imgcodecs.so.3.4
