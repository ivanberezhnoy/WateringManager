#-------------------------------------------------
#
# Project created by QtCreator 2016-07-22T09:28:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = WateringManager
CONFIG   += console
CONFIG   += c++11
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L/usr/lib -lwt -lwthttp -I/usr/local/include
LIBS += -L/usr/local/lib -lwthttp -lwt -lboost_regex -lboost_signals
LIBS += -lboost_system -lboost_thread -lboost_filesystem -lboost_date_time

SOURCES += main.cpp \
    src/Controller/DomController.cpp \
    src/DOM/SmartItem.cpp \
    src/Driver/DriverIO.cpp \
    src/IO/InputPin.cpp \
    src/IO/IOPin.cpp \
    src/IO/OutputPin.cpp \
    src/Utils/Logger.cpp

HEADERS += \
    src/Controller/DomController.h \
    src/DOM/SmartItem.h \
    src/Driver/DriverIO.h \
    src/IO/InputPin.h \
    src/IO/IOPin.h \
    src/IO/OutputPin.h \
    src/IO/PinDefs.h \
    src/Utils/Logger.h

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -std=c++11

INCLUDEPATH += "src"

OTHER_FILES += \
    settings.xml
