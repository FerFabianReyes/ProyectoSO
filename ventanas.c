WINDOW *crearVentana(int altura, int anchura, int posY, char *nombre)
{
    WINDOW *ventana = newwin(altura, anchura, posY, 0);
    box(ventana, 0, 0);
    mvwprintw(ventana, 0, 2, nombre);
    wrefresh(ventana);
    return ventana;
}