#-------------------------------------------------
#
# Project created by QtCreator 2018-12-06T12:43:16
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT       +=printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cource_work
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    registration.cpp \
    Programm.cpp \
    admin.cpp \
    user.cpp

HEADERS += \
        mainwindow.h \
    registration.h \
    Programm.h \
    admin.h \
    user.h

FORMS += \
        mainwindow.ui \
    registration.ui \
    admin.ui \
    user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target






