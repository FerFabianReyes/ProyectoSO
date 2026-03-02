#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <sys/select.h>
// gcc kbhead.c -lncurses

int kbhit(void);

int main()
{
    int i = 0;
    char cad[50];
    int max_y, max_x;

    initscr(); //inicializa ncurses
    cbreak(); // detecta las teclas sin tener que esperar el enter
    noecho(); // controlar que se puede poner en pantalla y que nno
    keypad(stdscr, TRUE); // Para detectar teclas especiales como backspace

    // Obtener tamaño de la terminal
    getmaxyx(stdscr, max_y, max_x);

    // --- Ventana superior: mostrar datos ---
    int win_top_h = (max_y * 2) / 3;
    WINDOW *win_top = newwin(win_top_h, max_x, 0, 0);
    box(win_top, 0, 0);
    mvwprintw(win_top, 0, 2, " Datos ");
    wrefresh(win_top);

    // --- Ventana inferior: recibir comandos ---
    int win_bot_h = max_y - win_top_h;
    WINDOW *win_bot = newwin(win_bot_h, max_x, win_top_h, 0);
    keypad(win_bot, TRUE); // Para detectar backspace dentro de la ventana
    box(win_bot, 0, 0);
    mvwprintw(win_bot, 0, 2, " Comandos ");
    mvwprintw(win_bot, 1, 1, "> ");
    wrefresh(win_bot);

    while (1)
    {
        // Mostrar datos en ventana superior
        mvwprintw(win_top, 1, 1, "Contador: %d", i);
        mvwprintw(win_top, 2, 1, "Ultimo comando: %-40s", cad);
        wrefresh(win_top);

        if (kbhit())
        {
            // Limpiar línea y redibujar prompt
            mvwprintw(win_bot, 1, 1, "> ");
            wclrtoeol(win_bot); // quita lo que se escribió antes a partir de la posición actual del cursor
            box(win_bot, 0, 0);
            mvwprintw(win_bot, 0, 2, " Comandos ");
            wrefresh(win_bot);

            int ch;
            int pos = 0;
            memset(cad, 0, sizeof(cad)); // llena la cadena con ceros

            // Forzar cursor visible
            curs_set(1);

            while (1)
            {
                // Mover cursor explícitamente antes de leer
                wmove(win_bot, 1, 3 + pos); 
                wrefresh(win_bot);

                ch = wgetch(win_bot); // sin mv, el cursor ya está en su lugar

                if (ch == '\n' || ch == '\r')
                    break;

                if (ch == KEY_BACKSPACE || ch == 127 || ch == 8)
                {
                    if (pos > 0)
                    {
                        pos--;
                        mvwaddch(win_bot, 1, 3 + pos, ' ');
                        wrefresh(win_bot);
                    }
                }
                else if (ch >= 32 && pos < 48)
                {
                    cad[pos] = (char)ch;
                    mvwaddch(win_bot, 1, 3 + pos, ch);
                    wrefresh(win_bot);
                    pos++;
                }
            }

            curs_set(0);
            cad[pos] = '\0';

            if (strcmp(cad, "salir") == 0)
                break;
        }
        i++;
        napms(100);
    }

    delwin(win_top);
    delwin(win_bot);
    endwin();
    return 0;
}

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