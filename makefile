all:
	g++ -o out CamadaFisica.cpp -Wall -ansi -std=c++11

test:
	g++ Simulador.cpp -o interface `pkg-config gtkmm-3.0 --cflags --libs`

clear:
	rm out

