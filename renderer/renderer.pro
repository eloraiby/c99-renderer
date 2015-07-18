#-------------------------------------------------
#
# Project created by QtCreator 2015-07-12T13:30:43
#
#-------------------------------------------------

#
# Used the glLoadGen to generate the gl_core_2_1 files, using:
#	lua LoadGen.lua -style=pointer_c -spec=gl -version=2.1 -profile=core core_2_1
#

QT       -= core gui

TARGET = renderer
TEMPLATE = lib
#CONFIG += staticlib

QMAKE_CFLAGS	+= -DBUILDING_RENDERING_DLL

unix {
	CONFIG	+= link_pkgconfig
	PKGCONFIG	+= glfw3
}

SOURCES += \
    renderer.c \
    gl_core_2_1.c \
    canvas.c

HEADERS += renderer.h \
    gl_core_2_1.h \
    internal/canvas.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../c99-3d-math/3dmath/release/ -l3dmath
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../c99-3d-math/3dmath/debug/ -l3dmath
else:unix: LIBS += -L$$OUT_PWD/../c99-3d-math/3dmath/ -l3dmath

INCLUDEPATH += $$PWD/../c99-3d-math/3dmath
DEPENDPATH += $$PWD/../c99-3d-math/3dmath
