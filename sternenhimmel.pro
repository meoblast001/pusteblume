CONFIG += c++14
QT += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = sternenhimmel
TEMPLATE = app

SOURCES += src/main.cpp \
           src/Sternenhimmel.cpp \
           src/Diaspora.cpp

HEADERS += src/Sternenhimmel.hpp \
           src/Diaspora.hpp \
           src/PostEntity.hpp

LIBS += -lmarkdown
