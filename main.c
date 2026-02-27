#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"
#include "estructuras.h"
Registros *reg = NULL;
// gcc main.c src/*.c -I./include
int main()
{

    Archivo *archivo = crearArchivo();
    reg = crearRegistro();

    detectarError(leerArchivo("archivo.txt", archivo));

    detectarError(tokenizar(archivo));
    
    detectarError(verifSintaxis(archivo));

    imprimirInstrucciones(archivo);
    
    liberarArchivo(archivo);

    return 0;
}