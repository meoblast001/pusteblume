QT += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pusteblume
TEMPLATE = app

SOURCES += src/main.cpp \
           src/Pusteblume.cpp

HEADERS += src/Pusteblume.hpp
