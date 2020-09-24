QT += widgets

HEADERS += ./Headers/AbstractWorld.h \
           ./Headers/CellularWorld.h \
           ./Headers/MainWindow.h \
           ./Headers/WorldWidget.h \
           ./Headers/utils.h

SOURCES += ./Sources/CellularWorld.cpp \
           ./Sources/main.cpp \
           ./Sources/MainWindow.cpp \
           ./Sources/WorldWidget.cpp \
           ./Sources/utils.cpp

TARGET = hellife


DESTDIR = .
OBJECTS_DIR = ./.objs
MOC_DIR= ./.mocs