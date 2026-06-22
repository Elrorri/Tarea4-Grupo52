#include "../include/tablaPersonas.h"

struct NodoHash{
    char DNpersonas[100];
    TPersonasLDE CDTpersonas;
};

struct rep_tablaPersonas {
    NodoHash** Tabla;
    int cantidad;
    int cota;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max){
    TTablaPersonas nuevo = new rep_tablaPersonas;
    nuevo->Tabla = new NodoHash*[max];
    nuevo->cantidad=0;
    nuevo->cota=max;
    for (int i=0;i<max;i++){
        nuevo->Tabla[i] = new NodoHash;
        nuevo->Tabla[i]->CDTpersonas=crearTPersonasLDE();
        strcpy(nuevo->Tabla[i]->DNpersonas, "");
    }
    return nuevo;
}

void insertarPersonaEnTTablaPersonas(TTablaPersonas &tabla, TPersona persona){
    nat indice = funcionDeDispersion(nombreTPersona(persona)) % tabla->cota;
    NodoHash* aux = tabla->Tabla[indice];
    insertarInicioDeTPersonasLDE(aux->CDTpersonas,persona);
    tabla->cantidad++;
}


void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
    nat indice =  funcionDeDispersion(nombre) % tabla->cota;
    NodoHash* aux = tabla->Tabla[indice];
    eliminarPersonaConNombreTPersonasLDE(aux->CDTpersonas,nombre);
    tabla->cantidad--;
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    nat indice =  funcionDeDispersion(nombre) % tabla->cota;
    NodoHash* aux = tabla->Tabla[indice];
    return estaPersonaConNombreEnTPersonasLDE(aux->CDTpersonas,nombre);
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    nat indice =  funcionDeDispersion(nombre) % tabla->cota;
    NodoHash* aux = tabla->Tabla[indice];
    return obtenerPersonaConNombreTPersonasLDE(aux->CDTpersonas,nombre);
}


void liberarTTablaPersonas(TTablaPersonas &tabla){
    for (int i=0; i<tabla->cota; i++){
        NodoHash* aux = tabla->Tabla[i];
        liberarTPersonasLDE(aux->CDTpersonas);
        delete aux;
    }
    delete[] tabla->Tabla;      
    delete tabla;
    tabla = NULL;
}


void imprimirTTablaPersonas(TTablaPersonas tabla){
    for (int i=0; i<tabla->cota; i++){
        imprimirTPersonasLDE(tabla->Tabla[i]->CDTpersonas);  
    }
}