#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
#include <vector>
#include <list>

using namespace std;


struct estado {
  int fila;
  int columna;
  int orientacion;
};

struct node{
    estado st;
    int indice_padre;
    Action accion_nodo;
    float coste_heuristica;
    float coste_total;

};

class ComportamientoJugador : public Comportamiento {
  public:

    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    estado destino;
    list<Action> plan;

    void calcularCosteTotal(node &nodo_actual, const node &nodo_final, const node &nodo_padre);
    node generarNodo(const node &nodo_padre, Action ac, const node &nodo_final);
    void aniadirListaCerrada(node nodo, vector<node> &lista_cerrada);
    void aniadirListaAbierta(node nodo, vector<node> &lista_abierta);
    bool esNodoFinal(node nodo, node nodo_final);
    bool pathFinding(const estado &origen, const estado &destino, list<Action> &plan);
    void PintaPlan(list<Action> plan);
    void ordenarListaAbierta(vector<node>& lista_abierta);
    void actualizarBrujula(Action accion);
};

#endif
