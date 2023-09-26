#pragma once
#include <string>
#include "cartas.hpp"
using namespace std;
class Jugador {
public: string nombre;
	  char tipo = 'M';
	  Cartas* mano = NULL;
	  Baraja* mesa;
	  int numeroCartasEnMano = 0;
	  void robarCartas(int numeroCartas);
	  int jugarMaquina();
	  int jugarHumano();
public:
	Jugador(string nombre, char tipo, Baraja* mesa);
	void mostrarMano();
	int jugar();
	void robarCarta();

};
