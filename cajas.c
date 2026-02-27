#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <sys/select.h>
//gcc kbhead.c -lncurses

int kbhit(void);

#define ROWS 2
#define COLS 6
#define CELL_H 3
#define CELL_W 16

char data[ROWS][COLS][50] = {
    {"PC",  "IR", "EAX", "EBX", "ECX", "EDX"},
    {"2",     "INC EAX",   "1", "1", "0", "2"}
};

void draw_table(int y, int x)
{
    for(int r = 0; r < ROWS; r++)
        for(int c = 0; c < COLS; c++)
        {
            WINDOW *cell = newwin(CELL_H, CELL_W, y + r*CELL_H, x + c*CELL_W);
            box(cell, 0, 0);
            mvwprintw(cell, 1, 2, "%s", data[r][c]);
            wrefresh(cell);
        }
}

int main()
{
    int i = 0;
    char cad[50];

    initscr();

    while(1)
    {
    draw_table(1, 1);

        mvprintw(15, 4, "Contador: %d", i);
        refresh();

        if(kbhit())
        {
            mvscanw(18, 5, "%49s", cad);
            if(strcmp(cad, "salir") == 0)
                break;
        }
        i++;
    }

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