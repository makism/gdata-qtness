#-------------------------------------------------
#
# Project created by QtCreator 2011-08-16T16:11:45
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = gdata-qtness-goauth2
TEMPLATE = lib

DEFINES += GDATAQTNESSGOAUTH2_LIBRARY

SOURCES += gdataqtnessgoauth2.cpp

HEADERS += gdataqtnessgoauth2.h\
        gdata-qtness-goauth2_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE9FC61B3
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = gdata-qtness-goauth2.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
