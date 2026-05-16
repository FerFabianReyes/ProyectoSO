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

void ejecutar(PCB *proceso, Grupo *grupo, Ventanas *ventanas)
{
    if (proceso->espera < 125) {
        proceso->espera++;
    } else {
        proceso->espera = 0;
        int res = ejecutarPrograma(proceso);
        proceso->quantum++;
        proceso->CPU += 20;
        grupo->GCPU += 20;
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
    if (!proceso->programa->tokenizado) {
        res = tokenizar(proceso->programa);
        if (res != BIEN) { return res; }
        
        res = verifSintaxis(proceso->programa);
        if (res != BIEN) { return res; }
        proceso->programa->tokenizado = 1;
    }
    return BIEN;
}

void dispatch(CabeceraGrupos *grupos, Nodo *nodoElegido, Cabecera *ejecuta, Ventanas *vent)
{
    Grupo *grupo = buscarGrupo(grupos, nodoElegido->proceso->idGrupo);
    sacarNodo(grupo->listos, nodoElegido->proceso->pid);
    
    if (nodoElegido->proceso->estado == NUEVO) {
        int res = revisarArchivo(nodoElegido->proceso);
        if (res != BIEN) {
            detectarError(vent->errores, res);
            free(nodoElegido);
            return;
        }
    }
    guardarRestaurarContexto(nodoElegido->proceso, 0);
    nodoElegido->proceso->estado = EJECUCION;
    agregarNodo(ejecuta, nodoElegido);
}

void registrarEnVista(Cabecera *vista, Nodo *nodo)
{
    Nodo *temp = vista->inicio;
    while (temp) {
        if (temp->proceso->pid == nodo->proceso->pid) { return; }
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
        impContextoProceso(ventanas->contexto, ventanas->maxX, temp->proceso, fila, temp->proceso->estado);
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

void roundRobin(CabeceraGrupos *grupos, Cabecera *ejecuta, Cabecera *terminados, Cabecera *vistaContexto, Ventanas *vent, int *cambioContexto)
{
    if (!ejecuta->inicio) {
        recalcularPrioridades(grupos);
        Nodo *nodoElegido = elegirProceso(grupos);
        if (!nodoElegido) {return; }
        
        dispatch(grupos, nodoElegido, ejecuta, vent);
        if (ejecuta->inicio) {
            registrarEnVista(vistaContexto, ejecuta->inicio);
            *cambioContexto = 1;
            limpiarVentana(vent->datos, " Datos ");
        } return;
    } 


    if (ejecuta->inicio) {
        PCB *proc = ejecuta->inicio->proceso;

        if (proc->estado == EJECUCION && !proc->IR) {
            proc->estado = TERMINADO;
        }

        if (proc->estado == TERMINADO || proc->estado == ESPERA) {
            guardarRestaurarContexto(proc, 1);
            Nodo *nodo = desencolarNodo(ejecuta);
            agregarNodo(terminados, nodo);
            *cambioContexto = 1;
        } else if (proc->estado == EJECUCION) { 
            if (proc->quantum >= 3) {
                proc->quantum = 0;
                guardarRestaurarContexto(proc, 1);
                Nodo *nodo = desencolarNodo(ejecuta);
                proc->estado = ESPERA;

                Grupo *grupo =buscarGrupo(grupos, proc->idGrupo);
                agregarNodo(grupo->listos, nodo);
                *cambioContexto = 1;
            } else {
                Grupo *grupo = buscarGrupo(grupos, proc->idGrupo);
                ejecutar(proc, grupo, vent); 
            }
        }
    }    
}

void guardarRestaurarContexto(PCB *proceso, int guardar)
{
    if (guardar) {
        proceso->regContex->EAX = registrosCPU->EAX;
        proceso->regContex->EBX = registrosCPU->EBX;
        proceso->regContex->ECX = registrosCPU->ECX;
        proceso->regContex->EDX = registrosCPU->EDX;
    } else {
        registrosCPU->EAX = proceso->regContex->EAX;
        registrosCPU->EBX = proceso->regContex->EBX;
        registrosCPU->ECX = proceso->regContex->ECX;
        registrosCPU->EDX = proceso->regContex->EDX;
    }
}

void recalcularPrioridades(CabeceraGrupos *grupos)
{
    float Wk = 1.0 / grupos->total;
    Grupo *grupo = grupos->inicio;

    while (grupo)
    {
        grupo->GCPU = grupo->GCPU / 2;
        Nodo *nodo = grupo->listos->inicio;

        while (nodo)
        {
            PCB *proc = nodo->proceso;
            proc->CPU = proc->CPU / 2;
            proc->prioridad = 60 + (proc->CPU / 2) + (grupo->GCPU  / (4 * Wk));
            nodo = nodo->sig;
        }
        grupo = grupo->sig;
    }
}

Nodo* elegirProceso(CabeceraGrupos *grupos)
{
    Nodo *ganador = NULL;
    Grupo *gruGanador = NULL;
    Grupo *grupo = grupos->inicio;

    while (grupo)
    {
        Nodo *nodo = grupo->listos->inicio;
        while (nodo)
        {
            if (!ganador || nodo->proceso->prioridad < ganador->proceso->prioridad) {
                ganador = nodo;
                gruGanador = grupo;
            }
            nodo = nodo->sig;
        }
        grupo = grupo->sig;
    }
    return ganador;
}

