#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <sys/select.h>
#include "prototipos.h"
#include "estructuras.h"
Registros *reg = NULL;

//gcc main.c -lncurses src/*.c -I./include -lm
int kbhit(void);

int main()
{
    int i=0, maxY, maxX;
    char cad[50];
    int pos = 0;
    int leyendo = 0;
    memset(cad, 0, sizeof(cad));

    initscr(); cbreak(); noecho();
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, maxY, maxX);

    WINDOW *ventanaDatos = crearVentana(maxY*3/5, maxX, 0, " Datos ");
    WINDOW *ventanaErrores = crearVentana(maxY/5, maxX, maxY*3/5, " Errores ");
    WINDOW *ventanaComandos = crearVentana(maxY/5, maxX, maxY*4/5, " Comandos ");
    nodelay(ventanaComandos, TRUE);
    limpiarComando(ventanaComandos);

    reg = crearRegistro();
    Archivo *archivo = crearArchivo();
    Ejecucion *ejecucion = crearEjecucion(archivo);

    while(1)
    {
        impEncabezado(ventanaDatos, maxX);

        if (ejecucion->estado == EJECUCION)
        {
            if (!ejecucion->IR) { ejecucion->estado = ESPERA; continue; }

            if (ejecucion->espera < 125) {
                ejecucion->espera++;
            } else {
                ejecucion->espera = 0;
                int res = ejecutarPrograma(ejecucion);
                if (res != BIEN) { ejecucion->estado = ESPERA; detectarError(ventanaErrores, res); }
                else {
                    impInstruccVentana(ventanaDatos, maxX, ejecucion);
                    ejecucion->IR = ejecucion->IR->sig;
                }
            }
        }

        if (kbhit()) {
            int caracter = wgetch(ventanaComandos);
            if (caracter == ERR) { napms(100); continue; }

            if (!leyendo) {
                leyendo = 1;
                pos = 0;
                memset(cad, 0, sizeof(cad));
                impVentanaComandos(ventanaComandos);
                curs_set(1);
            }

            if (caracter == '\n' || caracter == '\r') {
                cad[pos] = '\0';
                leyendo = 0;
                curs_set(0);

                limpiarVentana(ventanaErrores, " Errores ");
                limpiarComando(ventanaComandos);
                int comando = detectarComando(cad);
                char *nomArchivo = sacarNomArchivo(cad);

                if (comando == SALIR) { break; }
                if (comando == EJECUTAR_ARCHIVO) {
                    liberarEjecucion(ejecucion);
                    archivo = crearArchivo();
                    ejecucion = crearEjecucion(archivo);
                } else { detectarError(ventanaErrores, comando); }

                if (comando == EJECUTAR_ARCHIVO) {
                    int res = leerArchivo(nomArchivo, archivo);
                    if (res != BIEN) { detectarError(ventanaErrores, res); }
                    else {
                        res = tokenizar(archivo);
                        if (res != BIEN) { detectarError(ventanaErrores, res); }
                        else {
                            res = verifSintaxis(archivo);
                            if (res != BIEN) { detectarError(ventanaErrores, res); }
                            else {
                                ejecucion = crearEjecucion(archivo);
                                ejecucion->estado = EJECUCION;
                                limpiarVentana(ventanaDatos, " Datos ");
                            }
                        }
                    }
                }
            } else {
                leerComando(ventanaComandos, &pos, cad, caracter);
            }
        }

        i++;
        napms(16);
    }
    delwin(ventanaDatos);
    delwin(ventanaErrores);
    delwin(ventanaComandos);
    liberarEjecucion(ejecucion);
    free(reg);
    endwin();
    return 0;
}