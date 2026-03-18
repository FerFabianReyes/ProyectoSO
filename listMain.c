#include <stdio.h>
#include <string.h>
#include "prototipos.h"
int nProcesos = 0;

int main()
{
    Cabecera *listos = crearCabecera();
    Cabecera *ejecuta = crearCabecera();
    Cabecera *terminados = crearCabecera();
    Registros *registrosCPU = NULL;


    printf("listos: ");
    imprimirLista(listos);

    printf("ejecuta: ");
    imprimirLista(ejecuta);

    printf("terminados: ");
    imprimirLista(terminados);

    char *nom = "bien.asm";
    Archivo *arch = crearArchivo();
    leerArchivo(nom, arch);
    PCB *pcb0 = crearProceso(arch);
    PCB *pcb1 = crearProceso(arch);
    PCB *pcb2 = crearProceso(arch);

    Nodo *nodo1 = crearNodo(pcb0);
    Nodo *nodo2 = crearNodo(pcb1);
    Nodo *nodo3 = crearNodo(pcb2); 
    Nodo *aux = NULL;

    agregarNodo(listos, nodo1);
    agregarNodo(listos, nodo2);
    agregarNodo(listos, nodo3);

    printf("\nTodos los nodos en listos\n");
    printf("listos: ");
    imprimirLista(listos);

    printf("ejecuta: ");
    imprimirLista(ejecuta);

    printf("terminados: ");
    imprimirLista(terminados);
    
    printf("\nEl nodo 0 en ejecuta\n");
    aux = sacarNodo(listos, 0);
    agregarNodo(ejecuta, aux);

    printf("listos: ");
    imprimirLista(listos);

    printf("ejecuta: ");
    imprimirLista(ejecuta);

    printf("terminados: ");
    imprimirLista(terminados);

    printf("\nEl nodo 1 en ejecuta\n");
    aux = sacarNodo(listos, 1);
    agregarNodo(ejecuta, aux);

    printf("listos: ");
    imprimirLista(listos);

    printf("ejecuta: ");
    imprimirLista(ejecuta);

    printf("terminados: ");
    imprimirLista(terminados);

    printf("\nEl nodo 1 en terminados\n");
    aux = sacarNodo(ejecuta, 1);
    agregarNodo(terminados, aux);

    printf("listos: ");
    imprimirLista(listos);

    printf("ejecuta: ");
    imprimirLista(ejecuta);

    printf("terminados: ");
    imprimirLista(terminados);

}