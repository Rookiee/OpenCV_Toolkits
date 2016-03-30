#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T20:53:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCV
TEMPLATE = app

CONFIG += c++11 warn_on
SOURCES += main.cpp\
        mainwindow.cpp \
    erodedialog.cpp \
    addweighted.cpp \
    addresult.cpp \
    linearfilter.cpp \
    nonlinearfilter.cpp \
    Histogram/histogramwidget.cpp \
    Boundaries/boundaries.cpp \
    SplitBRG/splitbgr.cpp


HEADERS  += mainwindow.h \
    erodedialog.h \
    addweighted.h \
    qtheader.h \
    addresult.h \
    linearfilter.h \
    nonlinearfilter.h \
    publicfunctions.h \
    Histogram/histogramwidget.h \
    Boundaries/boundaries.h \
    SplitBRG/splitbgr.h


FORMS    += mainwindow.ui \
    erodedialog.ui \
    addweighted.ui \
    addresult.ui \
    linearfilter.ui \
    nonlinearfilter.ui \
    Histogram/histogramwidget.ui \
    Boundaries/boundaries.ui \
    SplitBRG/splitbgr.ui


RESOURCES += \
    resource.qrc

win32{

# 使用msvc编译的opencv
#INCLUDEPATH += C:\opencv\build\include
#INCLUDEPATH += C:\opencv\build\include\opencv2
#LIBS += -LC:\opencv\build\x64\vc12\lib

#LIBS += -lopencv_world310d


# 使用mingw gcc编译的opencv
INCLUDEPATH += C:\OpenCVMingw\include\
               C:\OpenCVMingw\include\opencv\
               C:\OpenCVMingw\include\opencv2\

LIBS+=  C:\OpenCVMingw\lib\libopencv_core310.dll.a\
#C:\OpenCVMingw\lib\libopencv_calib3d310.dll.a\
#C:\OpenCVMingw\lib\libopencv_contrib310.dll.a\
C:\OpenCVMingw\lib\libopencv_features2d310.dll.a\
#C:\OpenCVMingw\lib\libopencv_flann310.dll.a\
C:\OpenCVMingw\lib\libopencv_highgui310.dll.a\
C:\OpenCVMingw\lib\libopencv_imgproc310.dll.a\
C:\OpenCVMingw\lib\libopencv_imgcodecs310.dll.a\
#C:\OpenCVMingw\lib\libopencv_ml310.dll.a\
#C:\OpenCVMingw\lib\libopencv_objdetect310.dll.a\
#C:\OpenCVMingw\lib\libopencv_video310.dll.a
}

macx{
    INCLUDEPATH += /usr/local/include
    LIBS += -L/usr/local/lib
    LIBS += -lopencv_core\
            -lopencv_highgui\
            -lopencv_imgproc\
            -lopencv_imgcodecs\
            -lopencv_features2d
}
