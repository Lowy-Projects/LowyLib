#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T17:12:39
#
#-------------------------------------------------

QT += core gui
QT += widgets

TARGET = LowyLib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += lerror.cpp \
    llog.cpp

HEADERS += lerror.h \
    LowyLib.h \
    llog.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
