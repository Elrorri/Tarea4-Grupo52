#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct PrioHeap {
  nat Prioridad;
  nat PrioInv;
  TPersona persona;
};

struct rep_colaDePrioridadPersona {
  PrioHeap** cPri;
  nat cant;
  nat max;
  bool invertida;
};

TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona nuevo = new rep_colaDePrioridadPersona;
  nuevo->cPri = new PrioHeap*[N+1];
  nuevo->cant=0;
  nuevo->max=N;
  nuevo->invertida=false;
  for (nat i=0;i<N+1;i++){
    nuevo->cPri[i]=0;
    nuevo->cPri[i]=NULL;
  }
  return nuevo;
} 

TFecha obtenerFechaPrioridad(TPersona persona){
  TFecha f;
  f = fechaTEvento(primerEventoDeTPersona(persona));
  return f;
}

nat organizar_Prioridades(TPersona persona, TColaDePrioridadPersona &cp){
  nat aux = 1;
  for(nat i = 1; i <= cp->cant; i++){
    int comp = compararTFechas(obtenerFechaPrioridad(persona),
                              obtenerFechaPrioridad(cp->cPri[i]->persona));
    // si no invertida: fecha menor = más prioritaria 
    // si invertida: fecha mayor = más prioritaria 
    bool nuevaEsPeor;
    if(cp->invertida){
    nuevaEsPeor = (comp == -1);
    } else {
    nuevaEsPeor = (comp == 1);
    }
    if(nuevaEsPeor){
      aux++;
    } else {
      cp->cPri[i]->Prioridad++;
    }
  }
  return aux;
}


void filtrado_ascendente(nat pos, TColaDePrioridadPersona &cp){
  if (pos<=1)return;
  TPersona aux;
  nat Paux;
  if (cp->cPri[pos]->Prioridad < cp->cPri[pos/2]->Prioridad){
    aux=cp->cPri[pos]->persona;
    Paux=cp->cPri[pos]->Prioridad;
    cp->cPri[pos]->persona=cp->cPri[pos/2]->persona;
    cp->cPri[pos]->Prioridad=cp->cPri[pos/2]->Prioridad;
    cp->cPri[pos/2]->persona=aux;
    cp->cPri[pos/2]->Prioridad=Paux;
    pos=pos/2;
    filtrado_ascendente(pos,cp);
  }
}

void filtrado_descendente(nat pos, TColaDePrioridadPersona &cp){
  if (pos*2 > cp->cant) return; 
  nat hijoPri = pos*2;  
  
  // si tiene hijo derecho y tiene menor prioridad, ese es el candidato
  if (pos*2+1 <= cp->cant && 
      cp->cPri[pos*2+1]->Prioridad < cp->cPri[pos*2]->Prioridad){
    hijoPri = pos*2+1;
  }
  // si el hijo candidato tiene menor prioridad que el padre, cambio
  if (cp->cPri[hijoPri]->Prioridad < cp->cPri[pos]->Prioridad){
    TPersona auxPers = cp->cPri[pos]->persona;
    nat auxN = cp->cPri[pos]->Prioridad;
    cp->cPri[pos]->persona = cp->cPri[hijoPri]->persona;
    cp->cPri[pos]->Prioridad = cp->cPri[hijoPri]->Prioridad;
    cp->cPri[hijoPri]->persona = auxPers;
    cp->cPri[hijoPri]->Prioridad = auxN;
    filtrado_descendente(hijoPri, cp);
  }
}

void invertirPrioridad(TColaDePrioridadPersona &cp) {
  for(nat i = 1; i <= cp->cant; i++){
    cp->cPri[i]->Prioridad = (cp->cant + 1) - cp->cPri[i]->Prioridad;
  }
  for(int i = cp->cant/2; i >= 1; i--){
    filtrado_descendente(i, cp);
  }
  if (cp->invertida ==false){
    cp->invertida = true;
  }else{
    cp->invertida = false;
  }
}

void liberarCP(TColaDePrioridadPersona &cp) {
  for(nat i=1; i<=cp->cant; i++){
    liberarTPersona(cp->cPri[i]->persona);
    delete cp->cPri[i];  
  }
  delete[] cp->cPri;     
  delete cp;
  cp=NULL;
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp) {
  cp->cPri[cp->cant+1] = new PrioHeap;        
  cp->cPri[cp->cant+1]->persona = persona;
  cp->cPri[cp->cant+1]->Prioridad = organizar_Prioridades(persona, cp);
  cp->cant++;
  filtrado_ascendente(cp->cant, cp);
}
bool estaVaciaCP(TColaDePrioridadPersona cp) {
  return cp->cant==0;
}

TPersona prioritaria(TColaDePrioridadPersona cp) {
  return cp->cPri[1]->persona;
} 


void eliminarPrioritaria(TColaDePrioridadPersona &cp) {
  // si es vacia retorno
  if (estaVaciaCP(cp)) return;

  // libero la prioritaria
  liberarTPersona(cp->cPri[1]->persona);
  delete cp->cPri[1];  
  cp->cPri[1] = cp->cPri[cp->cant];
  cp->cPri[cp->cant] = NULL;
  cp->cant--;

  // reajusto para mantener las propiedades
  for(nat i = 1; i <= cp->cant; i++){
    cp->cPri[i]->Prioridad--;
  }

  // reordeno
  if (!estaVaciaCP(cp)){
    filtrado_descendente(1, cp);
  }
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
  for(nat i=1;i<=cp->cant ;i++){
    if (idTPersona(cp->cPri[i]->persona)==id)return true;
  }
  return false;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp){
  for(nat i=1;i<=cp->cant;i++){
    if (idTPersona(cp->cPri[i]->persona)==id){
        return fechaTEvento(primerEventoDeTPersona(cp->cPri[i]->persona));
    }
  }
  return NULL;
}