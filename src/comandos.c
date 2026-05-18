#include "prototipos.h"

void borrarCaracter(WINDOW *ventana, int *pos)
{
    (*pos)--;
    mvwaddch(ventana, 1, (*pos)+4, ' ');
    wmove(ventana, 1, (*pos)+4);
	wrefresh(ventana); 
}

void imprimirCaracter(WINDOW *ventana, int *pos, char cad[], int caracter)
{
    cad[*pos] = (char)caracter;
    mvwaddch(ventana, 1, (*pos)+4, caracter);
    wrefresh(ventana);
    (*pos)++;
}

void leerComando(WINDOW *ventana, int *pos, char cad[], int caracter)
{
    wmove(ventana, 1, (*pos)+4);
	wrefresh(ventana);

    if (caracter == KEY_BACKSPACE || caracter == 127) {
		if (*pos > 0) { borrarCaracter(ventana, pos);}

	} else if (caracter >= 32 && *pos < 48) {
		imprimirCaracter(ventana, pos, cad, caracter);
	}
}

int detectarComando(char cad[])
{
    if (strcmp(cad, "salir") == 0) { return SALIR; }
    regex_t regex;
    char *patron = "^ejecutar [^ ]+$";
    char *patronMatar = "^matar [0-9]+$";
    char *patronFork = "^fork [0-9]+ [0-9]+$";
    int resultado;

    resultado = regcomp(&regex, patron, REG_EXTENDED);
    resultado = regexec(&regex, cad, 0, NULL, 0);
    regfree(&regex);
    if (!resultado) { return EJECUTAR_ARCHIVO; }

    resultado = regcomp(&regex, patronMatar, REG_EXTENDED);
    resultado = regexec(&regex, cad, 0, NULL, 0);
    regfree(&regex);
    if (!resultado) { return MATAR_PROCESO; }

    resultado = regcomp(&regex, patronFork, REG_EXTENDED);
    resultado = regexec(&regex, cad, 0, NULL, 0);
    regfree(&regex);
    if (!resultado) { return FORK; }

    return COMANDO_INVALIDO; 
}

char *sacarNomArchivo(char cad[])
{
    char *nomArchivo = strchr(cad, ' ');
    if (nomArchivo) { return nomArchivo + 1; }
    else return NULL;
}

int procesarComando(char *cad, CabeceraGrupos *grupos, Cabecera *ejecuta, Cabecera *terminados, Cabecera *vista, Ventanas *vent)
{
    limpiarVentana(vent->errores, " Errores ");
    limpiarComando(vent->comandos);
    int comando = detectarComando(cad);

    if (comando == SALIR) { return SALIR; }
    if (comando != EJECUTAR_ARCHIVO && comando != MATAR_PROCESO && comando != FORK) { return comando; }

    if (comando == MATAR_PROCESO) {
        char *pidStr = sacarNomArchivo(cad);
        int pid = atoi(pidStr);

        Nodo *nodo = buscarNodoEnGrupos(grupos, pid);
        if (!nodo) { nodo = sacarNodo(ejecuta, pid); }
        if (!nodo) { return PROCESO_NO_ENCONTRADO; }

        nodo->proceso->estado = TERMINADO;
        agregarNodo(terminados, nodo);
        return BIEN;
    }

    if (comando == FORK) {
        char copia[50];
        strncpy(copia, cad, sizeof(copia));
        strtok(copia, " ");
        int pid     = atoi(strtok(NULL, " "));
        int noInstr = atoi(strtok(NULL, " "));

        Nodo *nodoPadre = buscarNodoEnGrupos(grupos, pid);
        if (!nodoPadre) { nodoPadre = buscarNodo(ejecuta, pid); }
        if (!nodoPadre) { return FORK_PID_INVALIDO; }

        PCB *padre = nodoPadre->proceso;

        Renglon *renInicio = irARenglon(padre->programa, noInstr);
        if (!renInicio) { return FORK_INSTR_INVALIDA; }

        Archivo *archHijo = copiarArchivoRenglon(renInicio);
        PCB *hijo = crearProceso(archHijo);

        hijo->IR = archHijo->inicio;
        hijo->nomArchivo = strdup(padre->nomArchivo);
        hijo->idGrupo = padre->idGrupo;
        hijo->estado = ESPERA;
        
        Grupo *grupoPadre = buscarGrupo(grupos, padre->idGrupo);
        Nodo *nodoHijo    = crearNodo(hijo);
        agregarNodo(grupoPadre->listos, nodoHijo);
        registrarEnVista(vista, nodoHijo);
        return BIEN;
    }
    

    Archivo *archivo = crearArchivo();
    char *nomArchivo = sacarNomArchivo(cad);

    int res = leerArchivo(nomArchivo, archivo);
    if (res != BIEN) { return res; }

    PCB *proceso = crearProceso(archivo);
    proceso->nomArchivo = strdup(nomArchivo);

    Grupo *nuevoGrupo = crearGrupo(grupos);
    proceso->idGrupo = nuevoGrupo->idGrupo;

    Nodo *proc = crearNodo(proceso);
    agregarNodo(nuevoGrupo->listos, proc);
    agregarGrupo(grupos, nuevoGrupo);
    registrarEnVista(vista, proc); 
    return BIEN;
}

Renglon* irARenglon(Archivo *prog, int noInstr)
{
    Renglon *actual = prog->inicio;
    int contador = 0;
    while (actual && contador < noInstr) {
        actual = actual->sig;
        contador++;
    }
    return actual;
}