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
    reg = crearRegistro();


	while(1)
	{
		//void impEncabezado();

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
				int res = leerArchivo(nomArchivo, archivo);

				if (res == BIEN) { continue; }
				else
				{
					mvwprintw(ventanaErrores, 1, 1, " no ");
					wrefresh(ventanaErrores); 
				}
			} 
		}
		i++;
		napms(100);
	}

	delwin(ventanaDatos);
	delwin(ventanaErrores);
	delwin(ventanaComandos);
	endwin();
	return 0;
}
