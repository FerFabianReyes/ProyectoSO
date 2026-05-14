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
    int anchCol = (maxX - 2) / 6;

    // Sub-ventana de 3 filas que ocupa las filas 1-3 dentro de ventana
    WINDOW *subEnc = derwin(ventana, 3, maxX - 2, 1, 1);
    box(subEnc, 0, 0);

    // Separadores verticales interiores
    for (int col = 1; col <= 5; col++) {
        int x = anchCol * col;
        mvwaddch(subEnc, 0, x, ACS_TTEE);
        mvwaddch(subEnc, 1, x, ACS_VLINE);
        mvwaddch(subEnc, 2, x, ACS_BTEE);
    }

    char *encabezado[] = {"PC", "IR", "EAX", "EBX", "ECX", "EDX"};
    for (int col = 0; col < 6; col++) {
        int x = anchCol * col + (anchCol - (int)strlen(encabezado[col])) / 2;
        mvwprintw(subEnc, 1, x, "%s", encabezado[col]);
    }

    wrefresh(subEnc);
    delwin(subEnc);
    wrefresh(ventana);
}

void impInstruccVentana(WINDOW *ventana, int maxX, PCB *proceso)
{
    int anchCol = (maxX - 2) / 6;
    char *ir = imprimirIR(proceso->IR);
    for (int i = 0; i < maxX-10; i++) {
        mvwprintw(ventana, 5, i+2, " ");
    }
    mvwprintw(ventana, 5, 8, " %d", proceso->PC);
    mvwprintw(ventana, 5, anchCol+4, " %s", ir);
    mvwprintw(ventana, 5, anchCol*2+8, " %d", registrosCPU->EAX);
    mvwprintw(ventana, 5, anchCol*3+8, " %d", registrosCPU->EBX);
    mvwprintw(ventana, 5, anchCol*4+8, " %d", registrosCPU->ECX);
    mvwprintw(ventana, 5, anchCol*5+8, " %d", registrosCPU->EDX);
    free(ir);  
    wrefresh(ventana);
}

void impContextoEncabezado(WINDOW *ventana, int maxX)
{
    int anchCol = (maxX - 2) / 6;
    int anchReg = anchCol * 3 / 7; //PC IR(2) EAX EBX ECX EDX

    WINDOW *subEnc = derwin(ventana, 3, maxX - 2, 1, 1);
    box(subEnc, 0, 0);

    for (int col = 1; col <= 3; col++) {
        int x = anchCol * col;
        mvwaddch(subEnc, 0, x, ACS_TTEE);
        mvwaddch(subEnc, 1, x, ACS_VLINE);
        mvwaddch(subEnc, 2, x, ACS_BTEE);
    }

    int xCtx = anchCol * 3;
    // PC=0, IR=1, EAX=3, EBX=4, ECX=5, EDX=6
    int colOffset[] = {0, 1, 3, 4, 5, 6};

    for (int col = 1; col <= 5; col++) {
        int x = xCtx + anchReg * colOffset[col];
        if (x < maxX - 2) {
            mvwaddch(subEnc, 0, x, ACS_TTEE);
            mvwaddch(subEnc, 1, x, ACS_VLINE);
            mvwaddch(subEnc, 2, x, ACS_BTEE);
        }
    }

    char *encabezado[] = {"PID", "Nombre", "Estado", "PC", "IR", "EAX", "EBX", "ECX", "EDX"};
    for (int col = 0; col < 3; col++) {
        int x = anchCol * col + (anchCol - (int)strlen(encabezado[col])) / 2;
        mvwprintw(subEnc, 1, x, "%s", encabezado[col]);
    }

    int anchReal[] = {1, 2, 1, 1, 1, 1};
    for (int col = 0; col < 6; col++) {
        int x = xCtx + anchReg * colOffset[col] + (anchReg * anchReal[col] - (int)strlen(encabezado[3 + col])) / 2;
        mvwprintw(subEnc, 1, x, "%s", encabezado[3 + col]);
    }

    wrefresh(subEnc);
    delwin(subEnc);
    wrefresh(ventana);
}

void impContextoProceso(WINDOW *ventana, int maxX, PCB *proceso, int fila, int estado)
{
    int anchCol = (maxX - 2) / 6;
    int anchReg = anchCol * 3 / 7;

    for (int i = 0; i < maxX - 2; i++) {
        mvwprintw(ventana, fila, i + 1, " ");
    }

    mvwprintw(ventana, fila, 1 + (anchCol - 3) / 2, "%d", proceso->pid);
    mvwprintw(ventana, fila, 1 + anchCol + (anchCol - strlen(proceso->nomArchivo)) / 2, "%s", proceso->nomArchivo);

    char *estadoStr;
    switch(estado) {
        case NUEVO:      estadoStr = "LISTO";     break;
        case EJECUCION:  estadoStr = "EJECUCION"; break;
        case ESPERA:     estadoStr = "LISTO";     break;
        case TERMINADO:  estadoStr = "TERMINADO"; break;
        default:         estadoStr = "";          break;
    }
    mvwprintw(ventana, fila, 1 + anchCol * 2 + (anchCol - strlen(estadoStr)) / 2, "%s", estadoStr);

    int xCtx = 1 + anchCol * 3;
    int colOffset[] = {0, 1, 3, 4, 5, 6};
    char *ir = imprimirIR(proceso->IR);
    mvwprintw(ventana, fila, xCtx + anchReg * colOffset[0] + 1, "%d", proceso->PC);
    mvwprintw(ventana, fila, xCtx + anchReg * colOffset[1] + 1, "%s", ir);
    mvwprintw(ventana, fila, xCtx + anchReg * colOffset[2] + 1, "%d", proceso->regContex->EAX);
    mvwprintw(ventana, fila, xCtx + anchReg * colOffset[3] + 1, "%d", proceso->regContex->EBX);
    mvwprintw(ventana, fila, xCtx + anchReg * colOffset[4] + 1, "%d", proceso->regContex->ECX);
    mvwprintw(ventana, fila, xCtx + anchReg * colOffset[5] + 1, "%d", proceso->regContex->EDX);
    free(ir);

    wrefresh(ventana);
}