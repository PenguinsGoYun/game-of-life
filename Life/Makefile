# Makefile for the Life class

playlife: life.o lifeboard.o
	g++ life.o lifeboard.o -o playlife

life.o: life.cpp lifeboard.h
	g++ -c -std=c++11 life.cpp -o life.o

lifeboard.o: lifeboard.cpp lifeboard.h
	g++ -c -std=c++11 lifeboard.cpp -o lifeboard.o

clean:
	rm *.o playlife

