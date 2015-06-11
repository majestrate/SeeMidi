#-------------------------------------------------
#
# Project created by QtCreator 2015-05-09T14:23:15
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeeMIDIv1
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    RtMidi.cpp \
    midifeedback.cpp \
    midivisualizer.cpp \
    johnwalkercolormaker.cpp

HEADERS  += mainwindow.h \
    RtMidi.h \
    midifeedback.h \
    midivisualizer.h \
    johnwalkercolormaker.h

FORMS    += mainwindow.ui
