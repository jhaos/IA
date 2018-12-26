/*
 * AlumnoBot.h
 *
 *  Created on: 15 ene. 2018
 *      Author: manupc
 */

#include "Bot.h"
#include <vector>
#ifndef MANUPCBOT_H_
#define MANUPCBOT_H_

struct NodoJuego{
	GameState estado;
	Move mov;
	int heuristica;
};

class boTijo:Bot {
public:
	int lvl;
	boTijo();
	~boTijo();

	void initialize();
	string getName();
	Move nextMove(const vector<Move> &adversary, const GameState &state);
	NodoJuego generarRaiz(GameState estado_actual, int h);
	NodoJuego alfaBeta(NodoJuego nodo, int lvl, NodoJuego alfa, NodoJuego beta, Player jugador);
	int calcularHeuristica (NodoJuego hijo, Player j);
};

#endif /* MANUPCBOT_H_ */
