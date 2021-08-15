QT       += core gui \
            network \
            svg \
            charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dayliwindow.cpp \
    digitalclock.cpp \
    forecastwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    navigationwindow.cpp \
    smarthome.cpp \
    traffic.cpp \
    weather.cpp

HEADERS += \
    dayliwindow.h \
    digitalclock.h \
    forecastwindow.h \
    mainwindow.h \
    navigationwindow.h \
    smarthome.h \
    traffic.h \
    weather.h

FORMS += \
    mainwindow.ui

OTHER_FILES += weather_icons/*

RESOURCES *= Zero_Widget.qrc

# Default rules for deployment.
target.path = /home/pi/$${TARGET}/bin
INSTALLS += target

DISTFILES += \
    Konfiguration.json \
    bvg_small.svg

