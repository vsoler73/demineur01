TEMPLATE = app

CONFIG += qt qglviewer 
QT += xml widgets gui opengl

FORMS = GameInterface.ui

RESOURCES = images.qrc

SOURCES = main.cpp \
          GameViewer.cpp \
	  GameInterface.cpp \
	  BoulderGame.cpp \
	  GameDrawer.cpp \
	  Level.cpp

HEADERS = GameViewer.h \
	  GameInterface.h \
	  BoulderGame.h \
	  GameDrawer.h \
          Level.h

OBJECTS_DIR = .obj
TARGET = boulder
