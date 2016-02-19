TEMPLATE = app
CONFIG += console c++11 -std=c++1y
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ACAutomation.cpp \
    KmpSearch.cpp \
    Matrix2DMatch.cpp

HEADERS += \
    ACAutomation.h \
    KmpSearch.h \
    Matrix2DMatch.h

