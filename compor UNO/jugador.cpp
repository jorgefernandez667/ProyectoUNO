#include "jugador.hpp"
using namespace std;
void Jugador::robarCartas(int numeroCartas) {
	for (int i = 0; i < numeroCartas; i++) {
		robarCarta();
	}
}
int Jugador::jugarMaquina() {
	int iCarta = 0;
	bool sigueJugando = true;
	Cartas* cartaEnMesa = mesa->cartaenjuego();
	Cartas* cartaActual = mano;
	while (sigueJugando) {
		if (cartaActual) {
			if (cartaActual->coincidepar(cartaEnMesa)) {
				if (cartaActual == mano) {
					mano = cartaActual->Siguiente;
				}
				cartaActual->retirar();
				mesa->cartaJugada(cartaActual);
				numeroCartasEnMano--;
				sigueJugando = false;
			}
			else {
				cartaActual = cartaActual->Siguiente;
			}
		}
		else {
			robarCarta();
			cartaActual = mano;
		}
	}
	return numeroCartasEnMano;

}

void Jugador::robarCarta() {
	Cartas* carta = mesa->robar();
	carta->Asignar_siguiente(mano);
	if (mano) {
		mano->Asignar_Anterior(carta);
	}
	mano = carta;
	numeroCartasEnMano++;
}
int Jugador::jugarHumano() {


	bool enJuego = true;
	while (enJuego) {
		mostrarMano();
		Cartas* carta = mesa->cartaenjuego();
		if (carta == NULL) {
			return 0;
		}
		std::cout << "Carta en la mesa: ";
		carta->Pintar();
		std::cout << "¿Carta a tirar?[1-" << numeroCartasEnMano << "](0 para Robar):";

		int idCartaJugar = -1;
		while (idCartaJugar<0 || idCartaJugar>numeroCartasEnMano) {
			std::cin >> idCartaJugar;
		}

		//we are looking for card
		idCartaJugar--;
		if (idCartaJugar >= 0) {
			enJuego = false;
			Cartas* cartaAJugar = mano->AdquirirCarta(idCartaJugar);
			if (cartaAJugar) {
				if (cartaAJugar == mano) {
					mano = cartaAJugar->Siguiente;
				}
				cartaAJugar->retirar();

				enJuego = !mesa->cartaJugada(cartaAJugar);
				if (enJuego) {
					std::cout << "Carta no válida\r\n ";
					cartaAJugar->Asignar_siguiente(mano);
					mano->Asignar_Anterior(cartaAJugar);
					mano = cartaAJugar;

				}
				else {
					numeroCartasEnMano--;
				}
			}

		}
		else if (idCartaJugar == -1) {
			robarCarta();
		}
	}

	return numeroCartasEnMano;
}

Jugador::Jugador(std::string nombre, char tipo, Baraja* mesa) {
	this->nombre = nombre;
	this->tipo = tipo;
	this->mesa = mesa;
}

void Jugador::mostrarMano() {
	int num = 0;
	if (mano) {
		num = mano->Pintar(true, true);
	}
	std::cout << "Cartas " << num << std::endl;
}

int Jugador::jugar() {
	int resultado = 0;
	switch (tipo) {
	case 'M':
		resultado = jugarMaquina();
		break;
	case 'H':
		resultado = jugarHumano();
		break;
	}
	return resultado;
}