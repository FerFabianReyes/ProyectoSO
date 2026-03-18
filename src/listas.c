#include "prototipos.h"
#include "estructuras.h"
Registros *registrosCPU = NULL;

Registros* inicializarRegistrosCPU()
{
    Registros *reg = malloc(sizeof(Registros));
    reg->EAX = 0; reg->EBX = 0;  
    reg->ECX = 0; reg->EDX = 0;
    return reg;
}

Cabecera* crearCabecera()
{
    Cabecera *nueva = malloc(sizeof(Cabecera));
    nueva->inicio = NULL;
    nueva->final = NULL;
    return nueva;
}

Nodo* crearNodo(PCB *pcb)
{
    Nodo *nuevo = malloc(sizeof(Nodo));
    nuevo->proceso = pcb;
    nuevo->sig = NULL;
    nuevo->ant = NULL;
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

Nodo *sacarNodo(Cabecera *cabecera, int pid)
{
    if (!cabecera->inicio) { return NULL; }
    
    Nodo *sacar = buscarNodo(cabecera, pid);
    
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

Nodo *buscarNodo(Cabecera *cabecera, int pid)
{   
    if (!cabecera->inicio) { return NULL; }
    
    Nodo *actual = cabecera->inicio;
    while (actual)
    {
        if (pid == actual->proceso->pid) {
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
        printf("[%d]", actual->proceso->pid);
        if (actual->sig) {
            printf(" -> ");
        }
        actual = actual->sig;
    }
    printf(" -> Fin\n");
}