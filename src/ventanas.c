#include "prototipos.h"

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

void limpiarVentana(WINDOW *ventana, char* nomVentana)
{
    wmove(ventana, 1, 1);
    wclrtoeol(ventana);
    box(ventana, 0, 0);
    mvwprintw(ventana, 0, 2, nomVentana);
    mvwprintw(ventana, 1, 1, " ");
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

void impEncabezado(WINDOW *ventana, int maxX)
{
    mvwhline(ventana, 1, 1, ACS_HLINE, maxX - 2);
    mvwhline(ventana, 3, 1, ACS_HLINE, maxX - 2);

    mvwaddch(ventana, 1, 1,        ACS_ULCORNER);
    mvwaddch(ventana, 1, maxX - 2, ACS_URCORNER);
    mvwaddch(ventana, 3, 1,        ACS_LLCORNER);
    mvwaddch(ventana, 3, maxX - 2, ACS_LRCORNER);

    int anchCol = (maxX - 2) / 6;

    for (int col = 1; col <= 5; col++) {
        int x = 1 + anchCol * col;
        mvwaddch(ventana, 1, x, ACS_TTEE);   // ┬
        mvwaddch(ventana, 2, x, ACS_VLINE);  // │
        mvwaddch(ventana, 3, x, ACS_BTEE);   // ┴
    }

    char *encabezado[] = {"PC", "IR", "EAX", "EBX", "ECX", "EDX"};
    for (int col = 0; col < 6; col++) {
        int x = 1 + anchCol * col + (anchCol - strlen(encabezado[col])) / 2;
        mvwprintw(ventana, 2, x, encabezado[col]);
    }
    wrefresh(ventana);
}

