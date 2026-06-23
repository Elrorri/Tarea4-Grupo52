#include "../include/aplicaciones.h"
#include "../include/colaDePrioridadPersona.h"
#include "../include/tablaPersonas.h"

void listarEnOrden(TTablaPersonas t, char** nombres, nat n){
    TColaDePrioridadPersona cola = crearCP(n);
    for(nat i=0; i<n; i++){
        insertarEnCP(copiarTPersona(obtenerPersonaDeTTablaPersonas(t, nombres[i])), cola);
    }
    while (!estaVaciaCP(cola)){
        imprimirTPersona(prioritaria(cola));
        eliminarPrioritaria(cola); 
    }
    liberarCP(cola);
}