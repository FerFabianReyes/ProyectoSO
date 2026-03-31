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
        impContextoEncabezado(ventanas->contexto, ventanas->maxX);


        if (proceso->estado == EJECUCION) {
            if (!proceso->IR) { proceso->estado = ESPERA; continue; }
            ejecutar(proceso, ventanas);
        }

        if (kbhit()) {
            int caracter = wgetch(ventanas->comandos);
            if (caracter == ERR) { napms(100); continue; }

            if (!leyendo) {
                iniciarLectura(ventanas, &pos, cad, &leyendo, sizeof(cad));
            }

            if (caracter == '\n' || caracter == '\r') {
                cad[pos] = '\0'; leyendo = 0;
                curs_set(0);
                int res = procesarComando(cad, &proceso, &archivo, ventanas);
                if (res == SALIR) { break; }
                if (res != BIEN) { detectarError(ventanas->errores, res); }
            } else {
                leerComando(ventanas->comandos, &pos, cad, caracter);
            }
        }

        i++;
        napms(16);
    }
    liberarInterfaz(ventanas, proceso);
    return 0;
}