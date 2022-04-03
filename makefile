all: CamadaFisica.o
	g++ Simulador.cpp -o Simulador `pkg-config gtkmm-3.0 --cflags --libs` CamadaFisica.o

CamadaFisica.o:
	g++ -c CamadaFisica.cpp -Wall -ansi -std=c++11

clear:
	rm CamadaFisica.o Simulador 