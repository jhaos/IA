/*
 * boTijo.cpp
 *
 *  Created on: 15 ene. 2018
 *      Author: julius
 */

#include "boTijo.h"
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;



int boTijo::calcularHeuristica(NodoJuego hijo, Player j){
	int buena, mala;
	Player otro, yo;
	bool uno = false;
	if (getPlayer() == J1){
		otro = J2;
		yo = J1;
		uno = true;
	}
	else{
		otro = J1;
		yo = J2;
	}
		buena = hijo.estado.getSeedsAt(getPlayer(),GRANERO);
		mala = hijo.estado.getSeedsAt(otro,GRANERO);
	
	int posibles_semillas = 0;

	for(int i=1; i <= 6 ; ++i){
		posibles_semillas += hijo.estado.getSeedsAt(j, (Position)i);
	}

	if (hijo.estado.isFinalState() && uno && (hijo.estado.getScore(yo) > 25)){
		buena += 10;
	}

	if(hijo.estado.getCurrentPlayer() == j){
		buena+=6;
	}
	buena*=3;
	

	
	
	return buena-mala + 2*posibles_semillas;
	
}

//Funcion para decir si el primer parametro es mayor que el segundo.
bool isMax(int valor_1, int valor_2){
	if (valor_1 > valor_2)
		return true;
	else return false;
}

NodoJuego boTijo::alfaBeta(NodoJuego nodo, int lvl, NodoJuego alfa, NodoJuego beta, Player j){
	
	if ( nodo.estado.isFinalState() || lvl == 12){
		nodo.heuristica = calcularHeuristica(nodo, j);
		return nodo;
	}
	if (getPlayer()==nodo.estado.getCurrentPlayer()){
		
		NodoJuego mejor;
		mejor.heuristica = alfa.heuristica;
		for (int i = 1; i < 7; ++i){

			if (nodo.estado.getSeedsAt(nodo.estado.getCurrentPlayer(),(Position) i) > 0){
				mejor.estado = nodo.estado.simulateMove((Move) i);
				mejor.mov = (Move) i;

				NodoJuego nuevo = alfaBeta(mejor, lvl+1, alfa, beta, mejor.estado.getCurrentPlayer());
				
				if (!isMax(mejor.heuristica, nuevo.heuristica)){
					mejor.heuristica = nuevo.heuristica;
					mejor.mov = (Move)i;
				}

				if (isMax(mejor.heuristica, alfa.heuristica)){
					alfa.heuristica = mejor.heuristica;
					alfa.mov = (Move)i;
				}

				if (beta.heuristica <= alfa.heuristica){
					return alfa;
				}
			}
		}
		return alfa;
	}else {
		
		NodoJuego peor;
		peor.heuristica = beta.heuristica;
		for (int i = 1; i < 7; ++i){

			//n_nodos++;
			//cerr << "n_nodos " << n_nodos << endl;
			if (nodo.estado.getSeedsAt(nodo.estado.getCurrentPlayer(),(Position) i) > 0){
				peor.estado = nodo.estado.simulateMove((Move) i);
				peor.mov = (Move) i;
			
				NodoJuego nuevo = alfaBeta(peor, lvl+1, alfa, beta, peor.estado.getCurrentPlayer());

				beta.mov = peor.mov;
				if (isMax(peor.heuristica, nuevo.heuristica)){
					peor.heuristica = nuevo.heuristica;
					//peor.mov = (Move) i;
				}
				if (!isMax(peor.heuristica, beta.heuristica)){
					beta.heuristica = peor.heuristica;
					//beta.mov = (Move) i;
				}

				

				if (beta.heuristica <= alfa.heuristica){
					return beta;
				}
			}
		}
		return beta;
	}
	
}



boTijo::boTijo() {
	// Inicializar las variables necesarias para ejecutar la partida
	srand(time(0));
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
	int lvl = 0;
	NodoJuego nodo_inicio, alfa, beta;
	nodo_inicio.estado = state;
	alfa.estado = state;
	alfa.heuristica = -100000;
	beta.estado = state;
	beta.heuristica = 100000;
	
	NodoJuego ultimo = alfaBeta(nodo_inicio, lvl, alfa, beta, state.getCurrentPlayer());
	// Implementar aquí la selección de la acción a realizar

	// OJO: Recordatorio. .
	// Para salidas por consola (debug) utilizar. Ejemplo:
	// << "Lo que quiero mostrar"<<;

	// OJO: Recordatorio. El nombre del bot y de la clase deben coincidir.
	// En caso contrario, el bot no podrá participar en la competición.
	// Se deberá sustituir el nombre AlumnoBot como nombre de la clase por otro
	// seleccionado por el alumno. Se deberá actualizar también el nombre
	// devuelto por el método getName() acordemente.

	movimiento = ultimo.mov;

	return movimiento;
}
