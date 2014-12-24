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
    hash.h

QMAKE_CFLAGS += -std=gnu11

DISTFILES += \
    md5.txt \
    md5header.txt
