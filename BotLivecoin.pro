#-------------------------------------------------
#
# Project created by QtCreator 2018-06-06T16:12:24
#
#-------------------------------------------------

QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BotLivecoin
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    JLivecoin/jbalance.cpp \
    JLivecoin/jlivecoin.cpp \
    JLivecoin/jmaxbidminask.cpp \
    JLivecoin/jorder.cpp \
    JLivecoin/jticker.cpp \
    JLivecoin/jwslivecoin.cpp \
    jsellorder.cpp \
    JLivecoin/jcandle.cpp \
    jtablmodel.cpp

HEADERS += \
        mainwindow.h \
    JLivecoin/jbalance.h \
    JLivecoin/jlivecoin.h \
    JLivecoin/jmaxbidminask.h \
    JLivecoin/jorder.h \
    JLivecoin/jticker.h \
    JLivecoin/jwslivecoin.h \
    jsellorder.h \
    JLivecoin/jcandle.h \
    jtablmodel.h

FORMS += \
        mainwindow.ui
