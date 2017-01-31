CONFIG += c++14
QT += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = sternenhimmel
TEMPLATE = app

SOURCES += src/main.cpp \
           src/Presentation.cpp \
           src/Diaspora.cpp \
           src/ControlPanel.cpp \
           src/PostWidget.cpp

HEADERS += src/Presentation.hpp \
           src/Diaspora.hpp \
           src/PostEntity.hpp \
           src/ControlPanel.hpp \
           src/PostWidget.hpp

LIBS += -lmarkdown
