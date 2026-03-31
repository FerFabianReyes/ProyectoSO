#include "prototipos.h"

Ventanas *inicializarInterfaz()
{
    Ventanas *ven = malloc(sizeof(Ventanas));
    initscr(); cbreak(); noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, ven->maxY, ven->maxX);

    ven->datos    = crearVentana(ven->maxY * 30 / 100, ven->maxX, 0, " Datos ");
    ven->contexto = crearVentana(ven->maxY * 40 / 100, ven->maxX, ven->maxY * 30 / 100, " Contexto ");
    ven->errores  = crearVentana(ven->maxY - 4 - ven->maxY * 70 / 100, ven->maxX, ven->maxY * 70 / 100, " Errores ");
    ven->comandos = crearVentana(4, ven->maxX, ven->maxY - 4," Comandos ");

    nodelay(ven->comandos, TRUE);
    limpiarComando(ven->comandos);
    return ven;
}

void ejecutar(PCB *proceso, Ventanas *ventanas)
{
    if (proceso->espera < 125) {
        proceso->espera++;
    } else {
        proceso->espera = 0;
        int res = ejecutarPrograma(proceso);
        if (res != BIEN) { proceso->estado = ESPERA; detectarError(ventanas->errores, res); }
        else {
             impInstruccVentana(ventanas->datos, ventanas->maxX, proceso);
                    proceso->IR = proceso->IR->sig;
                }
    }

}

void iniciarLectura(Ventanas *ventanas, int *pos, char *cad, int *leyendo, int tamCad)
{
    *leyendo = 1; *pos = 0;
    memset(cad, 0, tamCad);
    impVentanaComandos(ventanas->comandos);
    curs_set(1);
}

int procesarComando(char *cad, Cabecera *listos, Ventanas *vent)
{
    limpiarVentana(vent->errores, " Errores ");
    limpiarComando(vent->comandos);
    int comando = detectarComando(cad);

    if (comando == SALIR) { return SALIR; }
    if (comando != EJECUTAR_ARCHIVO) { detectarError(vent->errores, comando); return comando; }

    Archivo *archivo = crearArchivo();
    char *nomArchivo = sacarNomArchivo(cad);

    int res = leerArchivo(nomArchivo, archivo);
    if (res != BIEN) { return res; }

    PCB *proceso = crearProceso(archivo);
    proceso->nomArchivo = nomArchivo;
    Nodo *proc = crearNodo(proceso);
    agregarNodo(listos, proc);
    return BIEN;
}

int revisarArchivo(PCB *proceso)
{
    int res;
    res = tokenizar(proceso->programa);
    if (res != BIEN) { return res; }

    res = verifSintaxis(proceso->programa);
    if (res != BIEN) { return res; }
    return BIEN;
}

void dispatch(Cabecera *listos, Cabecera *ejecuta, Ventanas *vent)
{
    Nodo *nodo = desencolarNodo(listos);
    
    if (nodo->proceso->estado == NUEVO) {
        int res = revisarArchivo(nodo->proceso);
        if (res != BIEN) {
            detectarError(vent->errores, res);
            free(nodo);
            return;
        }
    }
    nodo->proceso->estado = EJECUCION;
    agregarNodo(ejecuta, nodo);
}

void liberarInterfaz(Ventanas *ven)
{
    delwin(ven->datos);
    delwin(ven->errores);
    delwin(ven->comandos);
    delwin(ven->contexto);
    free(registrosCPU);
    endwin();
}