#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
struct Cartas {
	enum TIPO { NORMAL, ROBO, SALTO, CAMBIO, COMODIN };
	string Color = "SIN ASIGNAR";
	int Numero;
	TIPO tipo;
	Cartas* Siguiente = NULL;
	Cartas* Anterior = NULL;
	Cartas(string Color, TIPO tipo, int Numero) {
		Asignar(Color, tipo, Numero);
	}
	Cartas() {

	}
	void Pintar();
	int Pintar(bool todos, bool enumerador=false);
	void Asignar(string Color,TIPO tipo,  int Numero) {
		this->Color = Color;
		this->Numero = Numero;
		this->tipo=tipo;
	}
	void Asignar_siguiente(Cartas* Cartas) {
		this->Siguiente = Cartas;
	}
	void Asignar_Anterior(Cartas* Cartas) {
		this->Anterior = Cartas;
	}
	Cartas* AdquirirCarta(int);
	void retirar();
	bool coincidepar(Cartas*);
	~Cartas() {
		if (Siguiente != NULL) {
			delete Siguiente;
		}
	}
};

class Baraja {
	int NumeroCartasMazo = 0;
	int NumeroCartasRestos = 0;
	Cartas* Mazo = NULL;
	Cartas* restos = NULL;
	string Nombrecartas[5] = { "Amarillo", "Rojo", "Verde", "Azul", "Negro" };
	Cartas* AñadircartaRestos(Cartas*, Cartas*);
public: 
	  Baraja();
	  void PintarMazo(bool todos=false);
	  void PintarRestos(bool todos=false);
	  void barajar(int numeropases);
	  bool cartaJugada(Cartas*);
	  Cartas* robar();
	  void incluir(Cartas*, int);
	  Cartas* cartaenjuego();
	  ~Baraja() {
	  if (Mazo!=NULL) {
		  delete Mazo;
	  }
	  
	  if (restos != NULL) {
		  delete restos;
	  }
}
	  int quedanmazo();
	  void recomponer();
};
