TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
include(../qtpropertybrowser-2.5_1-opensource/src/qtpropertybrowser.pri) \
HEADERS += nkjd.h \
 nkview.h \
 nkskala.h \
 mainwindow.h \
 nkhron.h \
 nkapsepoch.h \
 nkapsevent.h \
 nkrelepoch.h \
 nkrelevent.h \
 nkapsperson.h \
 nkrelperson.h \
 nkepoch.h
SOURCES += nkview.cpp \
 nkskala.cpp \
 mainwindow.cpp \
 main.cpp \
 nkhron.cpp \
 nkapsepoch.cpp \
 nkapsevent.cpp \
 nkrelepoch.cpp \
 nkrelevent.cpp \
 nkapsperson.cpp \
 nkrelperson.cpp \
 nkepoch.cpp
RESOURCES = ../epoch.qrc
target.path = Epoch
ICON = ../images/epoha.png
win32:RC_FILE = ../epoha.rc
symbian:include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
