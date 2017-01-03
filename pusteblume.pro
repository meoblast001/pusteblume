QT += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pusteblume
TEMPLATE = app

SOURCES += src/main.cpp \
           src/Pusteblume.cpp \
           src/Diaspora.cpp

HEADERS += src/Pusteblume.hpp \
           src/Diaspora.hpp
