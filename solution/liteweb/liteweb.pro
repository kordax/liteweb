#-------------------------------------------------
#
# Project created by QtCreator 2015-06-07T01:18:11
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

#TEMPLATE = lib

#SOURCES += ../../src/modules/interface.cpp
#HEADERS += ../../src/modules/interface.h
#DEFINES += LT_INTERFACE_H

TARGET = liteweb
TEMPLATE = app


SOURCES +=\
    ../../src/http/http.cpp \
    ../../src/main.cpp \
    ../../src/gui/ltmainwindow.cpp \
    ../../src/gui/ltlogwindow.cpp \
    ../../src/gui/ltlineedit.cpp \
    ../../src/gui/ltbutton.cpp \
    ../../src/helpers/fs.cpp \
    ../../src/gui/ltrootwindow.cpp \
    ../../src/modules/ltcore.cpp \
    ../../src/modules/ltsocket.cpp \
    ../../src/modules/ltworker.cpp \
    ../../src/modules/ltinterface.cpp

HEADERS  += \
    ../../src/const/headers.h \
    ../../src/http/http.h \
    ../../src/const/types.h \
    ../../src/config/config.h \
    ../../src/gui/ltmainwindow.h \
    ../../src/gui/ltlogwindow.h \
    ../../src/gui/ltlineedit.h \
    ../../src/gui/ltbutton.h \
    ../../src/helpers/fs.h \
    ../../src/gui/ltrootwindow.h \
    ../../src/const/messages.h \
    ../../src/modules/ltinterface.h \
    ../../src/modules/ltworker.h \
    ../../src/modules/ltsocket.h \
    ../../src/modules/ltcore.h

INCLUDEPATH += /home/kordax/Projects/liteweb/src

FORMS    +=

LIBS    += \
    -L/usr/local/include/boost/ \
    -lboost_filesystem \
    -lboost_system
