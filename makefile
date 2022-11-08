main: main.o indice_invertido.o
	g++ main.o indice_invertido.o -o main

main.o: main.cpp 
	g++ -c main.cpp -o main.o

indice_invertido.o: indice_invertido.cpp indice_invertido.h
	g++ -c indice_invertido.cpp -o indice_invertido.o