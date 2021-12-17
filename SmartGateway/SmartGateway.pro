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

#QT += multimediawidgets

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

RESOURCES += \
    res.qrc

DISTFILES +=

SUBDIRS += \
    appdemo/appdemo.pro

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lQt5Qmqtt
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lQt5Qmqttd

#INCLUDEPATH += $$PWD/.
#DEPENDPATH += $$PWD/.

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../5.9.1/mingw53_32/lib/ -lQt5Mqtt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../5.9.1/mingw53_32/lib/ -lQt5Mqttd
else:unix:!macx: LIBS += -L$$PWD/../../5.9.1/mingw53_32/lib/ -lQt5Mqtt

INCLUDEPATH += $$PWD/../../5.9.1/mingw53_32/include
DEPENDPATH += $$PWD/../../5.9.1/mingw53_32/include
