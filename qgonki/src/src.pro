SOURCES += qgonki.cpp \
           main.cpp
HEADERS += qgonki.h
TEMPLATE = app
CONFIG += release \
          warn_on \
	  thread \
          qt
TRANSLATIONS = ../translations/pl.ts
TARGET = ../bin/qgonki
