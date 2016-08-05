#-------------------------------------------------
#
# Project created by QtCreator 2016-07-26T12:59:08
#
#-------------------------------------------------

QT       += core gui network

static:win32:QMAKE_LFLAGS += -static-libgcc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RouterConf
TEMPLATE = app


SOURCES += main.cpp\
        qrconfdlg.cpp

HEADERS  += qrconfdlg.h

FORMS    += qrconfdlg.ui
