#-------------------------------------------------
#
# Project created by QtCreator 2011-02-28T19:31:08
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = sample-documentslist
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app


SOURCES += \
	main.cpp \
    clientlogin.cpp \
    documentslist.cpp \
    test_clientlogin.cpp

HEADERS += \
    clientlogin.h \
    documentslist.h \
    test_clientlogin.h
