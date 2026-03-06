#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <sys/select.h>
#include "prototipos.h"
#include "estructuras.h"
Registros *reg = NULL;

//gcc kbhead.c -lncurses src/*.c -I./include -lm
int kbhit(void);


int main()
{
	int i=0, maxY, maxX;
	char cad[50];

	initscr();	cbreak();	noecho();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, maxY, maxX);

	WINDOW *ventanaDatos = crearVentana(maxY*3/5, maxX, 0, " Datos ");
	WINDOW *ventanaErrores = crearVentana(maxY/5, maxX, maxY*3/5, " Errores ");
	WINDOW *ventanaComandos = crearVentana(maxY/5, maxX, maxY*4/5, " Comandos ");
	limpiarComando(ventanaComandos);
	

    Archivo *archivo = crearArchivo();
    Ejecucion *ejecucion = crearEjecucion(archivo);
    reg = crearRegistro();


	while(1)
	{
		impEncabezado(ventanaDatos, maxX);

		if(kbhit()) { 
			int caracter, pos = 0;
			memset(cad, 0, sizeof(cad));
			impVentanaComandos(ventanaComandos);
			curs_set(1);

			while (1)
			{
				caracter = wgetch(ventanaComandos);
				if (caracter == '\n' || caracter == '\r') { break; }
				leerComando(ventanaComandos, &pos, cad, caracter);
			}
			
			cad[pos] = '\0';
			int comando;
			limpiarComando(ventanaComandos);
			comando = detectarComando(cad);

			if (comando == SALIR) { break; }
			if (comando == EJECUTAR_ARCHIVO) {
				char *nomArchivo = sacarNomArchivo(cad);
				liberarEjecucion(ejecucion);
    			archivo = crearArchivo();
    			ejecucion = NULL;

    			int res = leerArchivo(nomArchivo, archivo);
				if (res == BIEN) {
					res = tokenizar(archivo);
					if (res != BIEN) {
						detectarError(ventanaErrores, res);
						continue;
					} else
					{
						ejecucion = crearEjecucion(archivo);
						limpiarVentana(ventanaDatos, " Datos ");
						impInstruccVentana(ventanaDatos, maxX, ejecucion);
						/*mvwprintw(ventanaDatos, 1, 1, "no hay error en tokenizar. Error: %d", res);
        				wrefresh(ventanaDatos);*/
						napms(500);
					}
					

					res = verifSintaxis(archivo);
					if (res != BIEN) {
						detectarError(ventanaErrores, res);
						continue;
					} else
					{
						limpiarVentana(ventanaDatos, " Datos ");
						mvwprintw(ventanaDatos, 1, 1, "no hay error en la sintaxis. Error: %d", res);
        				wrefresh(ventanaDatos);
						napms(1000);
					}
					
					
					ejecucion = crearEjecucion(archivo);
				} else {
					detectarError(ventanaErrores, res);
					continue;
				}
			} else {
					detectarError(ventanaErrores, comando);
					continue;
				}
		}
		i++;
		napms(100);
	}

	delwin(ventanaDatos);
	delwin(ventanaErrores);
	delwin(ventanaComandos);
	liberarEjecucion(ejecucion);
	free(reg);
	endwin();
	return 0;
}
