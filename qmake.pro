QT += widgets

HEADERS += ./Headers/AbstractWorld.h \
           ./Headers/CellularWorld.h \
           ./Headers/MainWindow.h \
           ./Headers/QWorldWidget.h \
           ./Headers/utils.h

SOURCES += ./Sources/CellularWorld.cpp \
           ./Sources/main.cpp \
           ./Sources/MainWindow.cpp \
           ./Sources/QWorldWidget.cpp \
           ./Sources/utils.cpp

TARGET = hellife


DESTDIR = .
OBJECTS_DIR = ./.objs
MOC_DIR= ./.mocs