#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <sys/select.h>
#include "prototipos.h"
#include "estructuras.h"
Registros *registrosCPU = NULL;
int nProcesos = 0;

//gcc main.c -lncurses src/*.c -I./include -lm
int kbhit(void);

int main()
{
    int i=0, pos = 0, leyendo = 0;
    char cad[50];
    memset(cad, 0, sizeof(cad));
    Ventanas *ventanas = inicializarInterfaz();

    registrosCPU = crearRegistro();
    Archivo *archivo = crearArchivo();
    PCB *proceso = crearProceso(archivo);
    Cabecera *listos = crearCabecera();
    Cabecera *ejecuta = crearCabecera();
    Cabecera *terminados = crearCabecera();

    while(1)
    {
        impEncabezado(ventanas->datos, ventanas->maxX);

        if (proceso->estado == EJECUCION) {
            if (!proceso->IR) { proceso->estado = ESPERA; continue; }
            ejecutar(proceso, ventanas);
        }

        if (kbhit()) {
            int caracter = wgetch(ventanas->comandos);
            if (caracter == ERR) { napms(100); continue; }

            if (!leyendo) {
                leyendo = 1;
                pos = 0;
                memset(cad, 0, sizeof(cad));
                impVentanaComandos(ventanas->comandos);
                curs_set(1);
            }

            if (caracter == '\n' || caracter == '\r') {
                cad[pos] = '\0';
                leyendo = 0;
                curs_set(0);

                limpiarVentana(ventanas->errores, " Errores ");
                limpiarComando(ventanas->comandos);
                int comando = detectarComando(cad);
                char *nomArchivo = sacarNomArchivo(cad);

                if (comando == SALIR) { break; }
                if (comando == EJECUTAR_ARCHIVO) {
                    liberarProceso(proceso);
                    archivo = crearArchivo();
                    proceso = crearProceso(archivo);
                } else { detectarError(ventanas->errores, comando); }

                if (comando == EJECUTAR_ARCHIVO) {
                    int res = leerArchivo(nomArchivo, archivo);
                    if (res != BIEN) { detectarError(ventanas->errores, res); }
                    else {
                        res = tokenizar(archivo);
                        if (res != BIEN) { detectarError(ventanas->errores, res); }
                        else {
                            res = verifSintaxis(archivo);
                            if (res != BIEN) { detectarError(ventanas->errores, res); }
                            else {
                                proceso = crearProceso(archivo);
                                proceso->estado = EJECUCION;
                                limpiarVentana(ventanas->datos, " Datos ");
                            }
                        }
                    }
                }
            } else {
                leerComando(ventanas->comandos, &pos, cad, caracter);
            }
        }

        i++;
        napms(16);
    }
    delwin(ventanas->datos);
    delwin(ventanas->errores);
    delwin(ventanas->comandos);
    liberarProceso(proceso);
    free(registrosCPU);
    endwin();
    return 0;
}