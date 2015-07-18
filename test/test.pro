#-------------------------------------------------
#
# Project created by QtCreator 2015-07-14T06:34:19
#
#-------------------------------------------------

QT       -= core gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.c


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../c99-3d-math/3dmath/release/ -l3dmath
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../c99-3d-math/3dmath/debug/ -l3dmath
else:unix: LIBS += -L$$OUT_PWD/../c99-3d-math/3dmath/ -l3dmath

INCLUDEPATH += $$PWD/../c99-3d-math/3dmath
DEPENDPATH += $$PWD/../c99-3d-math/3dmath

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../renderer/release/ -lrenderer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../renderer/debug/ -lrenderer
else:unix: LIBS += -L$$OUT_PWD/../renderer/ -lrenderer

INCLUDEPATH += $$PWD/../renderer
DEPENDPATH += $$PWD/../renderer
