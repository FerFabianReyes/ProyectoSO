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
    int i=0, pos = 0, leyendo = 0, cambioContexto = 0;;
    char cad[50];
    memset(cad, 0, sizeof(cad));
    Ventanas *ventanas = inicializarInterfaz();

    registrosCPU = crearRegistro();
    Cabecera *listos = crearCabecera();
    Cabecera *ejecuta = crearCabecera();
    Cabecera *terminados = crearCabecera();
    Cabecera *vistaContexto = crearCabecera();

   while(1)
    {
        impEncabezado(ventanas->datos, ventanas->maxX);
        impContextoEncabezado(ventanas->contexto, ventanas->maxX);
        if (cambioContexto) {
            actualizarContexto(vistaContexto, ventanas);
            cambioContexto = 0;
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
                int res = procesarComando(cad, listos, vistaContexto,ventanas);
                if (res == BIEN) { cambioContexto = 1; }
                if (res == SALIR) { break; }
                if (res != BIEN) { detectarError(ventanas->errores, res); }
            } else {
                leerComando(ventanas->comandos, &pos, cad, caracter);
            }
        }
        roundRobin(listos, ejecuta, terminados, vistaContexto, ventanas, &cambioContexto);    
        i++;
        napms(16);
    }
    liberarInterfaz(ventanas);
    return 0;
}