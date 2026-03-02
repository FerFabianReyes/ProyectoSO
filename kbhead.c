#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <sys/select.h>
#include "prototipos.h"
#include "estructuras.h"
Registros *reg = NULL;

//gcc kbhead.c -lncurses
int kbhit(void);


int main()
{
	int i=0;
	char cad[50];
	int maxY, maxX;

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, maxY, maxX);

	WINDOW *ventanaDatos = crearVentana(maxY*3/5, maxX, 0, " Datos ");
	WINDOW *ventanaErrores = crearVentana(maxY/5, maxX, maxY*3/5, " Errores ");
	WINDOW *ventanaComandos = crearVentana(maxY/5, maxX, maxY*4/5, " Comandos ");
	mvwprintw(ventanaComandos, 1, 1, " > ");
    wrefresh(ventanaComandos);

    reg = crearRegistro();

	while(1)
	{
		if(kbhit()) { 
			int caracter, pos = 0;
			memset(cad, 0, sizeof(cad));
			impVentanaComandos(ventanaComandos);

			curs_set(1);

			while (1)
			{
				wmove(ventanaComandos, 1, pos+4);
				wrefresh(ventanaComandos);
				caracter = wgetch(ventanaComandos);

				if (caracter == '\n' || caracter == '\r') { break; }

				if (caracter == KEY_BACKSPACE || caracter == 127 || caracter == 8 || caracter == 263) {
					if (pos > 0) {
						pos--;
						mvwaddch(ventanaComandos, 1, pos+4, ' ');
						wrefresh(ventanaComandos);
					}
				} else if (caracter >= 32 && pos < 48) {
					cad[pos] = (char)caracter;
					mvwaddch(ventanaComandos, 1, pos+4, caracter);
					wrefresh(ventanaComandos);
					pos++;
				}
			}
			curs_set(0);
			cad[pos] = '\0';
			if (strcmp(cad, "salir") == 0) { break; }
			limpiarComando(ventanaComandos);
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
