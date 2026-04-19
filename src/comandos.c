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
    int resultado;

    resultado = regcomp(&regex, patron, REG_EXTENDED);
    resultado = regexec(&regex, cad, 0, NULL, 0);
    regfree(&regex);

    if (!resultado) { return EJECUTAR_ARCHIVO; }
    else {return COMANDO_INVALIDO; }
    
}

char *sacarNomArchivo(char cad[])
{
    char *nomArchivo = strchr(cad, ' ');
    if (nomArchivo) { return nomArchivo + 1; }
    else return NULL;
}

int procesarComando(char *cad, Cabecera *listos, Cabecera *vista, Ventanas *vent)
{
    limpiarVentana(vent->errores, " Errores ");
    limpiarComando(vent->comandos);
    int comando = detectarComando(cad);

    if (comando == SALIR) { return SALIR; }
    if (comando != EJECUTAR_ARCHIVO) { return comando; }

    Archivo *archivo = crearArchivo();
    char *nomArchivo = sacarNomArchivo(cad);

    int res = leerArchivo(nomArchivo, archivo);
    if (res != BIEN) { return res; }

    PCB *proceso = crearProceso(archivo);
    proceso->nomArchivo = strdup(nomArchivo);
    Nodo *proc = crearNodo(proceso);
    agregarNodo(listos, proc);
    registrarEnVista(vista, proc); 
    return BIEN;
}