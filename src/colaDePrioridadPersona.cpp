#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct NodoHeap {
  TPersona persona;
  NodoHeap* der;
  NodoHeap* izq;
};

struct rep_colaDePrioridadPersona {
  NodoHeap* arb;
  nat* prioridad;
  nat cant;
  nat max;
};

TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona nuevo = new rep_colaDePrioridadPersona;
  nuevo->arb=new NodoHeap;
  nuevo->arb->persona=NULL;
  nuevo->arb->der = nuevo->arb->izq = NULL;
  nuevo->prioridad = new nat[N];
  nuevo->cant=0;
  nuevo->max=N;
  return nuevo;
} 

void invertirPrioridad(TColaDePrioridadPersona &cp) {

}

void liberarCP(TColaDePrioridadPersona &cp) {
  
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp) {
 
}

bool estaVaciaCP(TColaDePrioridadPersona cp) {
  return false;
}

TPersona prioritaria(TColaDePrioridadPersona cp) {
  return NULL;
} 

void eliminarPrioritaria(TColaDePrioridadPersona &cp) {
  
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
  return false;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp){
  return NULL;
}