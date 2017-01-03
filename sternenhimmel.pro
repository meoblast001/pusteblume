QT += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sternenhimmel
TEMPLATE = app

SOURCES += src/main.cpp \
           src/Sternenhimmel.cpp \
           src/Diaspora.cpp

HEADERS += src/Sternenhimmel.hpp \
           src/Diaspora.hpp
