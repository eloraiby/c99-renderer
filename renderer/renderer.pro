#-------------------------------------------------
#
# Project created by QtCreator 2015-07-12T13:30:43
#
#-------------------------------------------------

QT       -= core gui

TARGET = renderer
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    renderer.c

HEADERS += renderer.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
