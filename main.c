#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <sys/select.h>
#include "prototipos.h"
#include "estructuras.h"

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

    registrosCPU = crearRegistro();
    Archivo *archivo = crearArchivo();
    PCB *proceso = crearProceso(archivo);
    Cabecera *listos = crearCabecera();
    Cabecera *ejecuta = crearCabecera();
    Cabecera *terminados = crearCabecera();

    while(1)
    {
        impEncabezado(ventanaDatos, maxX);

        if (listos->inicio)
        {
            if (listos->inicio->proceso->estado == EJECUCION) {
                if (!proceso->IR) { proceso->estado = ESPERA; continue; }

                if (proceso->espera < 125) {
                    proceso->espera++;
                } else {
                    proceso->espera = 0;
                    int res = ejecutarPrograma(proceso);
                    if (res != BIEN) { proceso->estado = ESPERA; detectarError(ventanaErrores, res); }
                    else {
                        impInstruccVentana(ventanaDatos, maxX, proceso);
                        proceso->IR = proceso->IR->sig;
                    }
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
                    liberarProceso(proceso);
                    archivo = crearArchivo();
                    proceso = crearProceso(archivo);
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
                                proceso = crearProceso(archivo);
                                proceso->estado = EJECUCION;
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
    liberarProceso(proceso);
    free(registrosCPU);
    endwin();
    return 0;
}