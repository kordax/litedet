TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    list.h \
    walk.h \
    scan.h \
    const.h \
    preload.h

QMAKE_CFLAGS += -std=gnu11
QMAKE_CFLAGS += -g

DISTFILES +=
