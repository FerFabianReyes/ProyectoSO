#include <curses.h>
#include <sys/select.h>

int kbhit(void) 
{
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);

    if (select(1, &read_fd, NULL, NULL, &tv) == -1)
        return 0;

    if (FD_ISSET(0, &read_fd))
        return 1;

    return 0;
}

WINDOW *crearVentana(int altura, int anchura, int posY, char *nombre)
{
    WINDOW *ventana = newwin(altura, anchura, posY, 0);
    box(ventana, 0, 0);
    mvwprintw(ventana, 0, 2, nombre);
    wrefresh(ventana);
    return ventana;
}

void impVentanaComandos(WINDOW *ventana)
{
        mvwprintw(ventana, 1, 1, " > ");
		wclrtoeol(ventana);
		box(ventana, 0, 0);
        mvwprintw(ventana, 0, 2, " Comandos ");
		wrefresh(ventana); 
}

void limpiarComando(WINDOW *ventana)
{
    wmove(ventana, 1, 1);
    wclrtoeol(ventana);
    box(ventana, 0, 0);
    mvwprintw(ventana, 0, 2, " Comandos ");
    mvwprintw(ventana, 1, 1, " > ");
    wrefresh(ventana);
}

void borrarCaracter(WINDOW *ventana, int *pos)
{
    (*pos)--;
    mvwaddch(ventana, 1, (*pos)+4, ' ');
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
		if (*pos > 0) { borrarCaracter(ventana, pos); }

	} else if (caracter >= 32 && *pos < 48) {
		imprimirCaracter(ventana, pos, cad, caracter);
	}
}

