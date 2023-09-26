#include "cartas.hpp"
using namespace std;
Cartas* Baraja::AñadircartaRestos(Cartas* Carta, Cartas* actual) {
	if (actual == NULL) {
		Mazo = Carta;
	}
	else {
		Carta->Asignar_Anterior(actual);
		actual->Asignar_siguiente(Carta);
	}
	NumeroCartasMazo++;
	return Carta;
}



Baraja::Baraja(){
	Cartas* Actual = NULL;
	for (int i = 0; i < 4; i++) { //we add normal cards for each color
		Actual=AñadircartaRestos(new Cartas(Nombrecartas[i], Cartas::TIPO::NORMAL, 0),Actual);
		for (int j = 1; j <= 9; j++) {
			Actual=AñadircartaRestos(new Cartas(Nombrecartas[i], Cartas::TIPO::NORMAL, j),Actual);
			Actual=AñadircartaRestos(new Cartas(Nombrecartas[i], Cartas::TIPO::NORMAL, j), Actual);
		}
	}
	for (int i = 0; i < 4; i++) { //we add special cards for each color
		for (int j = 0; j < 2; j++) {
			Actual=AñadircartaRestos(new Cartas(Nombrecartas[i], Cartas::TIPO::CAMBIO, 0),Actual);
			Actual=AñadircartaRestos(new Cartas(Nombrecartas[i], Cartas::TIPO::SALTO, 0),Actual);
			Actual=AñadircartaRestos(new Cartas(Nombrecartas[i], Cartas::TIPO::ROBO, 2),Actual);
		}
	}
	for (int i = 0; i < 4; i++) { //we add wild cards
		Actual=AñadircartaRestos(new Cartas(Nombrecartas[4], Cartas::TIPO::ROBO, 4),Actual);
		Actual=AñadircartaRestos(new Cartas(Nombrecartas[4], Cartas::TIPO::COMODIN, 0),Actual);
	}
	barajar(2);
}

void Baraja::PintarMazo(bool todos){
	int num = Mazo->Pintar(todos);
	cout <<"cartas "<<num<< endl;
}
void Baraja::PintarRestos(bool todos)
{
	restos->Pintar(todos);
}
void Baraja::barajar(int numeropases) {
	for (int i = 0; i < numeropases; i++) {
		for (int j = 0; j < NumeroCartasMazo; j++) {
			Cartas* carta = robar();
			int random = rand() % NumeroCartasMazo;
			incluir(carta, random);
		}
	}
}
bool Baraja::cartaJugada(Cartas* carta) {

	if (restos) {
		if (!restos->coincidepar(carta)) {
			return false;
		}
		carta->Asignar_siguiente(restos);
		restos->Asignar_Anterior(carta);
	}
	cout << "Carta jugada ";
	carta->Pintar();
	restos = carta;
	NumeroCartasRestos++;
	return true;
}

Cartas* Baraja::robar() {
	Cartas* carta = Mazo;
	if (Mazo) {
		Mazo = Mazo->Siguiente;
		Mazo->Asignar_Anterior(NULL);
	}
	carta->Asignar_siguiente(NULL);
	NumeroCartasMazo--;
	return carta;
}

void Baraja::incluir(Cartas* carta, int posicion) {
	if (posicion <= 0) {
		carta->Asignar_siguiente(Mazo);
		Mazo->Asignar_Anterior(carta);
		Mazo = carta;
	}
	else {
		Cartas* c = Mazo;
		int i = 0;
		while (c->Siguiente != NULL && i < posicion) {
			c = c->Siguiente;
			i++;
		}
		carta->Asignar_Anterior(carta);
		carta->Asignar_siguiente(c->Siguiente);
		c->Asignar_siguiente(carta);

	}
	NumeroCartasMazo++;

}

Cartas* Baraja::cartaenjuego() {
	return restos;
}

int Baraja::quedanmazo() {
	return NumeroCartasMazo;
}

void Baraja::recomponer() {
	Mazo = restos->Siguiente;
	Mazo->Asignar_Anterior(NULL);
	restos->Asignar_siguiente(NULL);
	barajar(2);
}

void Cartas::Pintar() {
	std::cout << Color << " ";
	switch (tipo) {
	case Cartas::TIPO::CAMBIO:
		std::cout << "cambio de sentido";
		break;
	case Cartas::TIPO::SALTO:
		std::cout << "salto";
		break;
	case Cartas::TIPO::ROBO:
		std::cout << "+" << Numero;
		break;
	case Cartas::TIPO::COMODIN:
		std::cout << "cambio de color";
		break;
	default:
		std::cout << Numero;
		break;
	}

	std::cout << std::endl;
}

int Cartas::Pintar(bool mostrarTodas, bool numerado) {
	int idCarta = 0;
	if (mostrarTodas) {
		Cartas* cartaactual = this;
		while (cartaactual) {
			idCarta++;
			if (numerado) {
				std::cout << idCarta << " - ";
			}
			cartaactual->Pintar();
			cartaactual = cartaactual->Siguiente;
		}
	}
	else {

		idCarta++;
		Pintar();
	}

	return idCarta;
}

Cartas* Cartas::AdquirirCarta(int pos) {
	int i = 0;
	Cartas* cartaActual = this;
	while (i < pos && cartaActual) {
		i++;
		cartaActual = cartaActual->Siguiente;
	}
	return cartaActual;
}

void Cartas::retirar() {
	if (Anterior) {
		Anterior->Asignar_siguiente(Siguiente);
	}
	if (Siguiente) {
		Siguiente->Asignar_Anterior(Anterior);
	}
}

bool Cartas::coincidepar(Cartas* carta) {

	return carta->Numero == Numero || (carta->tipo == tipo && tipo != TIPO::NORMAL) || carta->Color == Color;
}

