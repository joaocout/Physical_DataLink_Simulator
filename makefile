all: CamadaFisica.o CamadaEnlace.o
	g++ Simulador.cpp -o Simulador `pkg-config gtkmm-3.0 --cflags --libs` CamadaFisica.o CamadaEnlace.o

CamadaFisica.o:
	g++ -c CamadaFisica.cpp

CamadaEnlace.o:
	g++ -c CamadaEnlace.cpp

clear:
	rm CamadaFisica.o rm CamadaEnlace.o Simulador 