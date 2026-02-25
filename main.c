#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"
#include "estructuras.h"
// gcc main.c src/*.c -I./include
int main()
{

    Archivo *archivo = crearArchivo();
    Registros *reg = crearRegistro();

    detectarError(leerArchivo("archivo.txt", archivo));

    detectarError(tokenizar(archivo));

    imprimirInstrucciones(archivo);
    
    liberarArchivo(archivo);

    return 0;
}