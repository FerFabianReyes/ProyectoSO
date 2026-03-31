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
    mvwprintw(ventana, 0, 2, "%s", nombre);
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
    mvwprintw(ventana, 0, 2, "%s", nomVentana);
    int maxY, maxX;
	getmaxyx(ventana, maxY, maxX);

    for (int i = 0; i < maxX-10; i++) {
        mvwprintw(ventana, 2, i+2, " ");
    }
    wrefresh(ventana);
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
        mvwprintw(ventana, 2, x, "%s", encabezado[col]);
    }
    wrefresh(ventana);
}

void impInstruccVentana(WINDOW *ventana, int maxX, PCB *proceso)
{
    int anchCol = (maxX - 2) / 6;
    for (int i = 0; i < maxX-10; i++) {
        mvwprintw(ventana, 5, i+2, " ");
    }
    mvwprintw(ventana, 5, 8, " %d", proceso->PC);
    mvwprintw(ventana, 5, anchCol+4, " %s", imprimirIR(proceso->IR));
    mvwprintw(ventana, 5, anchCol*2+8, " %d", registrosCPU->EAX);
    mvwprintw(ventana, 5, anchCol*3+8, " %d", registrosCPU->EBX);
    mvwprintw(ventana, 5, anchCol*4+8, " %d", registrosCPU->ECX);
    mvwprintw(ventana, 5, anchCol*5+8, " %d", registrosCPU->EDX);
    wrefresh(ventana);

}

void impContextoEncabezado(WINDOW *ventana, int maxX)
{
    mvwhline(ventana, 1, 1, ACS_HLINE, maxX - 2);
    mvwhline(ventana, 3, 1, ACS_HLINE, maxX - 2);

    mvwaddch(ventana, 1, 1,        ACS_ULCORNER);
    mvwaddch(ventana, 1, maxX - 2, ACS_URCORNER);
    mvwaddch(ventana, 3, 1,        ACS_LLCORNER);
    mvwaddch(ventana, 3, maxX - 2, ACS_LRCORNER);

    int anchCol = (maxX - 2) / 6;

    for (int col = 1; col <= 3; col++) {
        int x = 1 + anchCol * col;
        mvwaddch(ventana, 1, x, ACS_TTEE);
        mvwaddch(ventana, 2, x, ACS_VLINE);
        mvwaddch(ventana, 3, x, ACS_BTEE);
    }

    char *encabezado[] = {"PID", "Nombre", "Estado", "PC", "IR", "EAX", "EBX", "ECX", "EDX"};
    for (int col = 0; col < 3; col++) {
        int x = 1 + anchCol * col + (anchCol - strlen(encabezado[col])) / 2;
        mvwprintw(ventana, 2, x, "%s", encabezado[col]);
    }

    int xContexto = 1 + anchCol * 3;
    int anchReg = anchCol * 3 / 6;
    for (int col = 0; col < 6; col++) {
        int x = xContexto + anchReg * col + (anchReg - strlen(encabezado[3 + col])) / 2;
        mvwprintw(ventana, 2, x, "%s", encabezado[3 + col]);
    }

    wrefresh(ventana);
}
