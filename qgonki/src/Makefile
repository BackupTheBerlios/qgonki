
CC = g++
QTDIR = /opt/qt

All: 	qgonki

clean:
	rm *.o; rm qgonki

main.o: main.cpp
	$(CC) -I$(QTDIR)/include -c -o main.o main.cpp

qgonki.o: qgonki.cpp
	$(CC) -I$(QTDIR)/include -c -o qgonki.o qgonki.cpp

moc_qgonki.o: qgonki.h
	moc qgonki.h -o moc_qgonki.cpp
	$(CC) -I$(QTDIR)/include -c -o moc_qgonki.o moc_qgonki.cpp

qgonki: main.o qgonki.o moc_qgonki.o
	$(CC) -o qgonki -I/opt/qt/include/ main.o qgonki.o moc_qgonki.o -L/opt/qt/lib/ -lqt-mt

