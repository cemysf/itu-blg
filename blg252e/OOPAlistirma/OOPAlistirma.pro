TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    denklem.cpp \
    ifade.cpp \
    polinom.cpp \
    log.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    denklem.h \
    ifade.h \
    polinom.h \
    log.h

