# (c) by Marcin Wrochniak
# Distributed under GPL license.

GCC = g++
CC = gcc
QTDIR = /opt/qt
DESTDIR = 

All: 	../bin/qgonki ../bin/plconv

install:
	cp ../bin/* $(DESTDIR)/usr/bin/

uninstall:
	rm $(DESTDIR)/usr/bin/qgonki
	rm $(DESTDIR)/usr/bin/plconv

clean:
	rm *.o; rm ../bin/*

main.o: main.cpp
	$(GCC) -I$(QTDIR)/include -c -o main.o main.cpp

qgonki.o: qgonki.cpp
	$(GCC) -I$(QTDIR)/include -c -o qgonki.o qgonki.cpp

moc_qgonki.o: qgonki.h
	moc qgonki.h -o moc_qgonki.cpp
	$(GCC) -I$(QTDIR)/include -c -o moc_qgonki.o moc_qgonki.cpp

../bin/qgonki: main.o qgonki.o moc_qgonki.o
	$(GCC) -o ../bin/qgonki -I/opt/qt/include/ main.o qgonki.o moc_qgonki.o -L/opt/qt/lib/ -lqt-mt

../bin/plconv: plconv.c
	$(CC) plconv.c -o ../bin/plconv
