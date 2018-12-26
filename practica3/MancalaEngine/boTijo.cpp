/*
 * AlumnoBot.cpp
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "boTijo.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;
//Revisar esta heuristica

int boTijo::calcularHeuristica(NodoJuego hijo, Player j){
	int buena, mala;
	buena = hijo.estado.getSeedsAt(j,GRANERO);
	mala = hijo.estado.getSeedsAt((Player)1,GRANERO);
	return buena-mala;
	
}
//Funcion para decir si el primer parametro es mayor que el segundo.
bool isMax(int valor_1, int valor_2){
	if (valor_1 > valor_2)
		return true;
	else return false;
}

NodoJuego boTijo::alfaBeta(NodoJuego nodo, int lvl, NodoJuego alfa, NodoJuego beta, Player j){
	
	if (nodo.estado.getScore(j)>25 || lvl == 8){
		nodo.heuristica = calcularHeuristica(nodo, j);
		//bool s = nodo.estado.getScore(j)>25;
	//cerr << "NIVEL DE PROFUNCIDAD " << lvl <<"es true " << s << endl;
		return nodo;
	}
	if (j == J1){
		lvl++;
		NodoJuego mejor;
		mejor.heuristica = -1000000;
		for (int i = 1; i < 7; ++i){
			if (nodo.estado.getSeedsAt(j,(Position) i) > 0){
				mejor.estado = nodo.estado.simulateMove((Move) i);
				mejor.mov = (Move) i;

				NodoJuego nuevo = alfaBeta(mejor, lvl, alfa, beta, mejor.estado.getCurrentPlayer());

				if (!isMax(mejor.heuristica, nuevo.heuristica)){
					mejor.heuristica = nuevo.heuristica;
				}

				if (isMax(mejor.heuristica, alfa.heuristica)){
					alfa.heuristica = mejor.heuristica;
				}

				if (beta.heuristica <= alfa.heuristica){
					break;
				}
			}
		}
		return mejor;
	}else if (j == J2){
		lvl++;
		NodoJuego peor;
		peor.heuristica = 1000000;
		for (int i = 1; i < 7; ++i){
			if (nodo.estado.getSeedsAt(j,(Position) i) > 0){
				peor.estado = nodo.estado.simulateMove((Move) i);
				peor.mov = (Move) i;
			
				NodoJuego nuevo = alfaBeta(peor, lvl, alfa, beta, peor.estado.getCurrentPlayer());

				
				if (isMax(peor.heuristica, nuevo.heuristica)){
					peor.heuristica = nuevo.heuristica;
				}
				if (!isMax(peor.heuristica, beta.heuristica)){
					beta.heuristica = peor.heuristica;
				}

				//cerr << "hhh";

				if (beta.heuristica <= alfa.heuristica){
					break;
				}
			}
		}
		return peor;
	}
	
}



boTijo::boTijo() {
	// Inicializar las variables necesarias para ejecutar la partida

}

boTijo::~boTijo() {
	// Liberar los recursos reservados (memoria, ficheros, etc.)
}

void boTijo::initialize() {
	// Inicializar el bot antes de jugar una partida
}

string boTijo::getName() {
	return "boTijo"; // Sustituir por el nombre del bot
}

Move boTijo::nextMove(const vector<Move> &adversary, const GameState &state) {

	Move movimiento= M_NONE;
	lvl = 0;
	NodoJuego nodo_inicio, alfa, beta;
	nodo_inicio.estado = state;
	alfa.estado = state;
	alfa.heuristica = -100000;
	beta.estado = state;
	beta.heuristica = 100000;
	
	NodoJuego ultimo = alfaBeta(nodo_inicio, lvl, alfa, beta, state.getCurrentPlayer());
	// Implementar aquí la selección de la acción a realizar

	// OJO: Recordatorio. NO USAR cin NI cout.
	// Para salidas por consola (debug) utilizar cerr. Ejemplo:
	// cerr<< "Lo que quiero mostrar"<<endl;

	// OJO: Recordatorio. El nombre del bot y de la clase deben coincidir.
	// En caso contrario, el bot no podrá participar en la competición.
	// Se deberá sustituir el nombre AlumnoBot como nombre de la clase por otro
	// seleccionado por el alumno. Se deberá actualizar también el nombre
	// devuelto por el método getName() acordemente.

	movimiento = ultimo.mov;

	return movimiento;
}
