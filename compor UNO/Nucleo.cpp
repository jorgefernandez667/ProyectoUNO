#include <iostream>
#include "cartas.hpp"
#include "jugador.hpp"
using namespace std;
void main(int narg, char* arg) {
	Baraja baraja;

	int cartasRoboInicial = 7;
	int numeroJugadores = 2;
	string nombre;
	Jugador** jugadores = new Jugador * [numeroJugadores]();
	printf("esciba su nombre: ");
	cin >> nombre;
	cout << endl;

	jugadores[0] = new Jugador(nombre, 'H', &baraja);
	for (int i = 1; i < numeroJugadores; i++) {
		jugadores[i] = new Jugador("Maquina " + i, 'M', &baraja);
	}

	for (int i = 0; i < cartasRoboInicial; i++) {
		for (int iJugador = 0; iJugador < numeroJugadores; iJugador++) {
			jugadores[iJugador]->robarCarta();
		}

	}


	//Suponemos que se levanta una por defecto
	baraja.cartaJugada(baraja.robar());
	bool siguePartida = true;
	while (siguePartida) {
		for (int iJugador = 0; iJugador < numeroJugadores && siguePartida; iJugador++) {
			std::cout << "Esta jugando " << jugadores[iJugador]->nombre << std::endl;
			std::cout << "Quedan en mazo " << baraja.quedanmazo() << std::endl;
			int leQuedan = jugadores[iJugador]->jugar();
			if (leQuedan == 0) {
				std::cout << "Ha ganado " << jugadores[iJugador]->nombre << std::endl;
				siguePartida = false;
			}
			else {
				std::cout << "Le quedan  " << leQuedan << std::endl;
			};
			if (siguePartida && baraja.quedanmazo() == 0) {
				baraja.recomponer();
			}
		}system("cls");
	}


	for (int i = 0; i < numeroJugadores; i++) {
		if (jugadores[i]) {
			delete jugadores[i];
		}
	}
	delete[] jugadores;
}