#-------------------------------------------------
#
# Project created by QtCreator 2018-05-23T16:56:00
#
#-------------------------------------------------

QT       += core gui sql network concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project
TEMPLATE = app

 INCLUDEPATH+=include


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
    signup.cpp \
    login.cpp \
    creategroup.cpp \
    createchannel.cpp \
    widget.cpp \
    WellcomePage.cpp

HEADERS += \
    signup.h \
    login.h \
    creategroup.h \
    createchannel.h \
    widget.h \
    WellcomePage.h

FORMS += \
    signup.ui \
    login.ui \
    creategroup.ui \
    createchannel.ui \
    widget.ui \
    WellcomePage.ui

DISTFILES += \
    Test1Form.ui.qml \
    Test1.qml

RESOURCES += \
    icons.qrc \
    qml.qrc
