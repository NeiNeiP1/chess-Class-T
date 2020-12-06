QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
TARGET = Ajedrez
TEMPLATE = app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alfil.cpp \
    board.cpp \
    button.cpp \
    caballo.cpp \
    casilla.cpp \
    juego.cpp \
    main.cpp \
    peon.cpp \
    pieza.cpp \
    reina.cpp \
    rey.cpp \
    torre.cpp

HEADERS += \
    alfil.h \
    board.h \
    button.h \
    caballo.h \
    casilla.h \
    juego.h \
    peon.h \
    pieza.h \
    reina.h \
    rey.h \
    torre.h

FORMS +=



RESOURCES += \
    resource.qrc
