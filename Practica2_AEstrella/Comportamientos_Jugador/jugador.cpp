#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <list>
#include <vector>

using namespace std;


void ComportamientoJugador::actualizarBrujula(Action accion){

    switch(accion) {
        case actFORWARD:
            if (brujula == 0)
                fil--;
            else if (brujula == 1)
                col++;
            else if (brujula == 2)
                fil++;
            else if (brujula == 3)
                col--;
            break;
        case actTURN_R:
            if (brujula == 0)
                brujula = 1;
            else if (brujula == 1)
                brujula = 2;
            else if (brujula == 2)
                brujula = 3;
            else if (brujula == 3)
                brujula = 0;
            break;

        case actTURN_L:
            if (brujula == 0)
                brujula = 3;
            else if (brujula == 1)
                brujula = 0;
            else if (brujula == 2)
                brujula = 1;
            else if (brujula == 3)
                brujula = 2;
            break;
    }
}

void ComportamientoJugador::calcularCosteTotal( node &nodo_actual, const node &nodo_final, const node &nodo_padre) {
    float por_hueco = 1;
    float h_fila;
    float h_columna;

    h_fila = abs(nodo_actual.st.fila - nodo_final.st.fila);
    h_columna = abs(nodo_actual.st.columna - nodo_final.st.columna);
    //if (nodo_actual.accion_nodo == actFORWARD) {
    nodo_actual.coste_heuristica = h_fila + h_columna;
    nodo_actual.coste_total = nodo_actual.coste_heuristica + por_hueco + nodo_padre.indice_padre;
   // }else{
      //nodo_actual.coste_total = por_hueco;
   // } //PONGO ESTO AUNQUE NO LLEGUE EN ALGUNOS MAPAS?
}

node ComportamientoJugador::generarNodo(const node &nodo_padre, Action ac, const node &nodo_final) {
    node siguiente_nodo;

    if (ac == actFORWARD){

        switch (nodo_padre.st.orientacion){
            case 0:
                siguiente_nodo.st = nodo_padre.st;
                if (siguiente_nodo.st.fila > 0)
                    siguiente_nodo.st.fila = siguiente_nodo.st.fila-1;
                break;
            case 1:
                siguiente_nodo.st = nodo_padre.st;
                siguiente_nodo.st.columna = siguiente_nodo.st.columna+1;
                break;
            case 2:
                siguiente_nodo.st = nodo_padre.st;
                siguiente_nodo.st.fila = siguiente_nodo.st.fila+1;
                break;
            case 3:
                siguiente_nodo.st = nodo_padre.st;
                if (siguiente_nodo.st.columna > 0)
                    siguiente_nodo.st.columna = siguiente_nodo.st.columna-1;
                break;
            default:
                cout << "Ese no es un valor correcto" << endl;
                break;
        }
        siguiente_nodo.accion_nodo = actFORWARD;
        calcularCosteTotal(siguiente_nodo, nodo_final, nodo_padre);

    }else if (ac == actTURN_L){
        switch(nodo_padre.st.orientacion) {
            case 0:
                siguiente_nodo.st = nodo_padre.st;
                siguiente_nodo.st.orientacion = 3;
                break;
            case 1:
                siguiente_nodo.st = nodo_padre.st;
                siguiente_nodo.st.orientacion = 0;
                break;
            case 2:
                siguiente_nodo.st = nodo_padre.st;
                siguiente_nodo.st.orientacion = 1;
                break;
            case 3:
                siguiente_nodo.st = nodo_padre.st;
                siguiente_nodo.st.orientacion = 2;
                break;
            default:
                cout << "Ese no es un valor correcto" << endl;
                break;
        }

        siguiente_nodo.accion_nodo = actTURN_L;
        calcularCosteTotal(siguiente_nodo, nodo_final, nodo_padre);

    }else if (ac == actTURN_R) {
        switch(nodo_padre.st.orientacion) {

            case 0:
                siguiente_nodo.st = nodo_padre.st;
                siguiente_nodo.st.orientacion = 1;
                break;
            case 1:
                siguiente_nodo.st = nodo_padre.st;
                siguiente_nodo.st.orientacion = 2;
                break;
            case 2:
                siguiente_nodo.st = nodo_padre.st;
                siguiente_nodo.st.orientacion = 3;
                break;
            case 3:
                siguiente_nodo = nodo_padre;
                siguiente_nodo.st.orientacion = 0;
                break;
            default:
                cout << "Ese no es un valor correcto" << endl;
                break;
        }
        siguiente_nodo.accion_nodo = actTURN_R;
        calcularCosteTotal(siguiente_nodo, nodo_final, nodo_padre);
    }



    return siguiente_nodo;
}


void ComportamientoJugador::aniadirListaCerrada(node nodo, vector<node> &lista_cerrada){
    lista_cerrada.push_back(nodo);
}

void ComportamientoJugador::aniadirListaAbierta(node nodo, vector<node> &lista_abierta){

	lista_abierta.push_back(nodo);
    ordenarListaAbierta(lista_abierta);
}



void ComportamientoJugador::ordenarListaAbierta(vector<node>& lista_abierta) {
    int min;
    node aux;
    if (lista_abierta.size() > 1){
        for (int i = 0; i < lista_abierta.size() - 1; ++i) {
            min = i;
            for (int j = i + 1; j < lista_abierta.size(); ++j) {
                if (lista_abierta[min].coste_total < lista_abierta[j].coste_total) {
                    min = j;
                }
                aux = lista_abierta[min];
                lista_abierta[min] = lista_abierta[i];
                lista_abierta[i] = aux;
            }
        }
    }
}

bool ComportamientoJugador::esNodoFinal(node nodo, node nodo_final){
    bool es_igual = false;

    if ((nodo.st.fila == nodo_final.st.fila) && (nodo.st.columna == nodo_final.st.columna)){
        es_igual = true;
    }

    return es_igual;
}

void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}

void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}

void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}

bool comprobarEnCerrada(const vector<node> &lista_cerrados, const node &nodo){
    bool comprobante = false;

    for (int i =0; i < lista_cerrados.size(); ++i){
        if (lista_cerrados[i].st.fila == nodo.st.fila && lista_cerrados[i].st.columna == nodo.st.columna
            && lista_cerrados[i].st.orientacion == nodo.st.orientacion)
            comprobante = true;
    }


    return comprobante;
}

bool comprobarEnAbierta(const vector<node> &lista_abierta, const node &nodo){
    bool comprobante = false;

    for (int i =0; i < lista_abierta.size(); ++i){
        if (lista_abierta[i].st.fila == nodo.st.fila && lista_abierta[i].st.columna == nodo.st.columna
            && lista_abierta[i].st.orientacion == nodo.st.orientacion)
            comprobante = true;
    }
    return comprobante;
}


bool ComportamientoJugador::pathFinding(const estado &origen, const estado &destino, list<Action> &plan) {
    int indice_cerrados = -1;
    node nodo_final;
    node nodo_inicial;
    vector<node> lista_abierta;
    vector<node> lista_cerrada;

    nodo_inicial.indice_padre = -1;
    nodo_inicial.accion_nodo = actIDLE;
    nodo_inicial.st.columna = origen.columna;
    nodo_inicial.st.fila = origen.fila;
    nodo_inicial.st.orientacion = 0;
    nodo_final.st.columna = destino.columna;
    nodo_final.st.fila = destino.fila;

	if (nodo_inicial.st.columna != nodo_final.st.columna && nodo_inicial.st.fila != nodo_final.st.fila
            && nodo_inicial.st.orientacion != nodo_final.st.orientacion){
		lista_abierta.push_back(nodo_inicial);
	}


	while (!lista_abierta.empty()){
        node nodo_actual = lista_abierta.back();

        if (esNodoFinal(nodo_actual, nodo_final)){
            while (nodo_actual.indice_padre != -1){
                plan.push_back(nodo_actual.accion_nodo);
                nodo_actual = lista_cerrada[nodo_actual.indice_padre];
            }
            PintaPlan(plan);
            return true;
        }
        else{
        	bool adelante_esta_en_cerrada = false;
			bool der_esta_en_cerrada = false;
			bool izq_esta_en_cerrada = false;
			bool adelante_esta_en_abierta = false;
			bool der_esta_en_abierta = false;
			bool izq_esta_en_abierta = false;

        	lista_abierta.pop_back();
        	aniadirListaCerrada(nodo_actual, lista_cerrada);
            indice_cerrados++;
        	//Buscar nodos adyacentes del nodo actual.
			node nodo_adelante = generarNodo(nodo_actual, actFORWARD, nodo_final);
			node nodo_der = generarNodo(nodo_actual, actTURN_R, nodo_final);
			node nodo_izq = generarNodo(nodo_actual, actTURN_L, nodo_final);

			nodo_adelante.indice_padre = indice_cerrados;
			nodo_der.indice_padre = indice_cerrados;
			nodo_izq.indice_padre = indice_cerrados;

            adelante_esta_en_abierta = comprobarEnAbierta(lista_abierta, nodo_adelante);
            izq_esta_en_abierta = comprobarEnAbierta(lista_abierta, nodo_izq);
            der_esta_en_abierta = comprobarEnAbierta(lista_abierta, nodo_der);
			adelante_esta_en_cerrada = comprobarEnCerrada(lista_cerrada, nodo_adelante);
            izq_esta_en_cerrada = comprobarEnCerrada(lista_cerrada, nodo_izq);
            der_esta_en_cerrada = comprobarEnCerrada(lista_cerrada, nodo_der);


			bool posible_adelante = (mapaResultado[nodo_adelante.st.fila][nodo_adelante.st.columna] == 'S'
							 || mapaResultado[nodo_adelante.st.fila][nodo_adelante.st.columna] == 'K') ||
							 mapaResultado[nodo_adelante.st.fila][nodo_adelante.st.columna] == 'T';

			bool posible_der = (mapaResultado[nodo_der.st.fila][nodo_der.st.columna] == 'S'
								 || mapaResultado[nodo_der.st.fila][nodo_der.st.columna] == 'K') ||
								 mapaResultado[nodo_der.st.fila][nodo_der.st.columna] == 'T';

			bool posible_izq = (mapaResultado[nodo_izq.st.fila][nodo_izq.st.columna] == 'S'
								 || mapaResultado[nodo_izq.st.fila][nodo_izq.st.columna] == 'K') ||
								 mapaResultado[nodo_izq.st.fila][nodo_izq.st.columna] == 'T';

			if ((!adelante_esta_en_cerrada && !adelante_esta_en_abierta) && posible_adelante)
				aniadirListaAbierta(nodo_adelante, lista_abierta);
			if ((!der_esta_en_cerrada && !der_esta_en_abierta) && posible_der)
				aniadirListaAbierta(nodo_der, lista_abierta);
			if ((!izq_esta_en_cerrada && !izq_esta_en_abierta) && posible_izq)
				aniadirListaAbierta(nodo_izq, lista_abierta);

        }


	}

    return false;
}


Action ComportamientoJugador::think(Sensores sensores) {


    Action accionActual;
    bool encuentra_camino = false;
	if (plan.size() == 0){
		estado origen, destino;
		origen.fila = sensores.mensajeF;
		origen.columna = sensores.mensajeC;
		origen.orientacion = 0;
        if (sensores.mensajeF == -1 || sensores.mensajeC == -1) {
            return actIDLE;
        }

        if (sensores.vida == 0){
            plan.clear();
        }
		destino.fila = sensores.destinoF;
		destino.columna = sensores.destinoC;

		if (!pathFinding(origen, destino, plan)){
		    cout << "Objetivo no alcanzable" << endl;
		}else{
		    cout << "Objetivo encontrado" << endl;
		}

		return actIDLE;

	}else{
        accionActual = plan.back();
		//plan.pop_back();
        if (sensores.superficie[2] == 'a'){
	        return actIDLE;
        }

        plan.pop_back();
        return accionActual;
	}

}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
