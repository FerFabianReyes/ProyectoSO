#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"
#include "archivos.c"
#include "tokens.c"


int main()
{
    Archivo *archivo = crearArchivo();

    leerArchivo("archivo.txt", archivo);

    imprimirArchivo(archivo);

    tokenizar(archivo);

    imprimirTokens(archivo);
    
    liberarArchivo(archivo);

    return 0;
}