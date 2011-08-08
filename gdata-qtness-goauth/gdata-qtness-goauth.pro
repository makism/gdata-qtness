#-------------------------------------------------
#
# Project created by QtCreator 2011-03-18T20:25:45
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = gdata-qtness-goauth
TEMPLATE = lib
CONFIG   += dll crypto crypto_prl
CONFIG   -= app_bundle

DEFINES += GDATAQTNESSGOAUTH_LIBRARY

SOURCES += \
    requesttoken.cpp

HEADERS +=\
        gdata-qtness-goauth_global.h \
    gdata-qtness-goauth_namespace.h \
    requesttoken.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}
