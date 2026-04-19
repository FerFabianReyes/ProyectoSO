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
        if (res != BIEN) { proceso->estado = TERMINADO; detectarError(ventanas->errores, res); }
        else {
            impInstruccVentana(ventanas->datos, ventanas->maxX, proceso);
            if (proceso->estado != TERMINADO) {
                proceso->IR = proceso->IR->sig;
            }
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

void registrarEnVista(Cabecera *vista, Nodo *nodo)
{
    Nodo *temp = vista->inicio;
    while (temp) {
        if (temp->proceso->pid == nodo->proceso->pid) {
            return;
        }
        temp = temp->sig;
    }
    Nodo *copia = crearNodo(nodo->proceso);
    agregarNodo(vista, copia);
}

static int filaContexto = 4;  // empieza después del encabezado

void actualizarContexto(Cabecera *vista, Ventanas *ventanas)
{
    int fila = 4;
    int maxY, maxX;
    getmaxyx(ventanas->contexto, maxY, maxX);
    int maxFilas = maxY - 2;

    Nodo *temp = vista->inicio;
    while (temp && fila < maxFilas) {
        impContextoProceso(ventanas->contexto, ventanas->maxX, temp->proceso, fila);
        fila++;
        temp = temp->sig;
    }
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

void roundRobin(Cabecera *listos, Cabecera *ejecuta, Cabecera *terminados, Cabecera *vistaContexto, Ventanas *vent, int *cambioContexto)
{
    if (!ejecuta->inicio && listos->inicio) {
        dispatch(listos, ejecuta, vent);
        if (ejecuta->inicio) { registrarEnVista(vistaContexto, ejecuta->inicio); }
        *cambioContexto = 1;
        limpiarVentana(vent->datos, " Datos ");
    } 

    if (ejecuta->inicio) {
        PCB *proc = ejecuta->inicio->proceso;

        if (proc->estado == EJECUCION && !proc->IR) {
            proc->estado = TERMINADO;
        }

        if (proc->estado == TERMINADO || proc->estado == ESPERA) {
            Nodo *nodo = desencolarNodo(ejecuta);
            agregarNodo(terminados, nodo);
            registrarEnVista(vistaContexto, terminados->final); 
            *cambioContexto = 1;
        } else  if (proc->estado == EJECUCION) { ejecutar(proc, vent); }
    }    
}