exe/main: build/main.o build/indice_invertido.o
	g++ build/main.o build/indice_invertido.o -o exe/main
	
exe/main_DB: build/main.o build/indice_invertido.o
	g++ -g build/main.o build/indice_invertido.o -o main_DB

testes/teste: build/indice_invertido.o testes/indice_invertido_teste.cpp
	g++ testes/indice_invertido_teste.cpp build/indice_invertido.o -Isrc -o testes/teste

build/main.o: src/main.cpp 
	g++ -c src/main.cpp -o build/main.o

build/indice_invertido.o: src/indice_invertido.cpp src/indice_invertido.h
	g++ -c src/indice_invertido.cpp -o build/indice_invertido.o