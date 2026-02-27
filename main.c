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
    Ejecucion *ejec = crearEjecucion(archivo);

    detectarError(leerArchivo("archivo.txt", ejec->programa));

    detectarError(tokenizar(ejec->programa));
    
    detectarError(verifSintaxis(ejec->programa));

    imprimirInstrucciones(ejec->programa);
    
    liberarArchivo(archivo);

    return 0;
}