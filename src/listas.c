#include "prototipos.h"
#include "estructuras.h"

Cabecera* crearCabecera()
{
    Cabecera *nueva = malloc(sizeof(Cabecera));
    nueva->inicio = NULL;
    nueva->final = NULL;
    return nueva;
}

Nodo* crearNodo()
{
    Nodo *nuevo = malloc(sizeof(Nodo));
    nuevo->proceso = NULL;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    nuevo->numProceso = nProcesos;
    nProcesos++;
    return nuevo;
}

void agregarNodo(Cabecera *cabecera, Nodo *nodo)
{
    if (cabecera->inicio) {
        nodo->ant = cabecera->final;
        nodo->sig = NULL;
        cabecera->final->sig = nodo;
        cabecera->final = nodo;
        
    } else {
        cabecera->inicio = nodo;
        cabecera->final = nodo;        
    }
}

Nodo *sacarNodo(Cabecera *cabecera, int numProceso)
{
    if (!cabecera->inicio) { return NULL; }
    
    Nodo *sacar = buscarNodo(cabecera, numProceso);
    
    if (!sacar) { return NULL; }
    
    if (cabecera->inicio == cabecera->final) {
        cabecera->inicio = NULL;
        cabecera->final = NULL;
    }
    else if (sacar == cabecera->inicio) {
        cabecera->inicio = sacar->sig;
        cabecera->inicio->ant = NULL;
    }
    else if (sacar == cabecera->final) {
        cabecera->final = sacar->ant;
        cabecera->final->sig = NULL;
    }
    else {
        sacar->ant->sig = sacar->sig;
        sacar->sig->ant = sacar->ant;
    }
    sacar->sig = NULL;
    sacar->ant = NULL;
    return sacar;
}

Nodo *buscarNodo(Cabecera *cabecera, int numProceso)
{   
    if (!cabecera->inicio) { return NULL; }
    
    Nodo *actual = cabecera->inicio;
    while (actual)
    {
        if (numProceso == actual->numProceso) {
            return actual;
        }
        actual = actual->sig;
    } 
    return NULL;
}

void imprimirLista(Cabecera *cabecera)
{    
    Nodo *actual = cabecera->inicio;
    while (actual)
    {
        printf("[%d]", actual->numProceso);
        if (actual->sig) {
            printf(" -> ");
        }
        actual = actual->sig;
    }
    printf(" -> Fin\n");
}