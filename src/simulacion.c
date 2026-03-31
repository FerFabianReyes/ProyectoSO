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

int procesarComando(char *cad, PCB **proceso, Archivo **archivo, Ventanas *vent)
{
    limpiarVentana(vent->errores, " Errores ");
    limpiarComando(vent->comandos);
    int comando = detectarComando(cad);
    char *nomArchivo = sacarNomArchivo(cad);

    if (comando == SALIR) { return SALIR; }
    if (comando != EJECUTAR_ARCHIVO) { detectarError(vent->errores, comando); return comando; }

    liberarProceso(*proceso);
    *archivo = crearArchivo();
    *proceso = crearProceso(*archivo);

    int res = leerArchivo(nomArchivo, *archivo);
    if (res != BIEN) { return res; }

    res = tokenizar(*archivo);
    if (res != BIEN) { return res; }

    res = verifSintaxis(*archivo);
    if (res != BIEN) { return res; }

    *proceso = crearProceso(*archivo);
    (*proceso)->estado = EJECUCION;
    limpiarVentana(vent->datos, " Datos ");
    return BIEN;
}

void liberarInterfaz(Ventanas *ven, PCB *proceso)
{
    delwin(ven->datos);
    delwin(ven->errores);
    delwin(ven->comandos);
    delwin(ven->contexto);
    liberarProceso(proceso);
    free(registrosCPU);
    endwin();
}