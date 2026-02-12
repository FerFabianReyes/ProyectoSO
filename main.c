#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "estructuras.c"

int main()
{
    Archivo *archivo = crearArchivo();

    leerArchivo("archivo.txt", archivo);

    imprimirArchivo(archivo);

    limpiarRenglones(&archivo);

    imprimirTokens(archivo);
    
    liberarArchivo(archivo);

    return 0;
}