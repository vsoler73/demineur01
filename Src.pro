TEMPLATE = app

CONFIG += qt qglviewer 
QT += xml widgets gui opengl

FORMS = GameInterface.ui

RESOURCES = images.qrc

SOURCES = main.cpp \
          GameViewer.cpp \
          GameInterface.cpp \
          GameDrawer.cpp \
          Level.cpp

HEADERS = GameViewer.h \
	  GameInterface.h \
          GameDrawer.h \
          Level.h \
          GameDefs.h

OBJECTS_DIR = .obj
TARGET = demineur
