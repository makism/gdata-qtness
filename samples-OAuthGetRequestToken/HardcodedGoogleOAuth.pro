#-------------------------------------------------
#
# Project created by QtCreator 2011-03-14T18:01:02
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = HardcodedGoogleOAuth
CONFIG   += console crypto crypto_prl
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    fetchoauthrequesttoken.cpp

HEADERS += \
    fetchoauthrequesttoken.h
