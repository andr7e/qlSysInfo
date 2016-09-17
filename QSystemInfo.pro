#-------------------------------------------------
#
# Project created by QtCreator 2012-12-01T22:20:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSystemInfo
TEMPLATE = app


SOURCES += main.cpp\
        systeminfo.cpp \
    system.cpp \
    release.cpp \
    motherboard.cpp \
    memory.cpp \
    lspci.cpp \
    cpu.cpp \
    utils.cpp

HEADERS  += systeminfo.h \
    utils.h

FORMS    += systeminfo.ui

RESOURCES += \
    resource.qrc
