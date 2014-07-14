#-------------------------------------------------
#
# Project created by QtCreator 2014-06-02T11:20:01
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = canopycover
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    dialogintro.cpp \
    clsmngpictures.cpp \
    psepicture.cpp \
    imageviewer.cpp \
    frmreport.cpp \
    frmCond.cpp \
    pseCanopyCover.cpp

HEADERS  += \
    mainwindow.h \
    dialogintro.h \
    clsmngpictures.h \
    psepicture.h \
    imageviewer.h \
    frmreport.h \
    frmCond.h \
    pseCanopyCover.h

FORMS    += \
    mainwindow.ui \
    dialogintro.ui \
    imageviewer.ui \
    frmreport.ui \
    frmCond.ui \
    frmCond.ui

RESOURCES += \
    icon.qrc

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += D:\\opencv-2.4.3\\static\\release\\include

LIBS += -LD:\\opencv-2.4.3\\static\\release\\lib \
-lopencv_calib3d243 \
-lopencv_features2d243 \
-lopencv_highgui243 \
-lopencv_flann243 \
-lopencv_imgproc243 \
-lopencv_core243

LIBS += -LD:\\opencv-2.4.3\\static\\release\\share\\OpenCV\\3rdparty\\lib \
-lIlmImf \
-llibjasper \
-llibjpeg \
-llibpng \
-llibtiff \
-lzlib

LIBS += -mwindows -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lole32 -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32 -lwininet
