#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototipos.h"
#include "archivos.c"
#include "tokens.c"
#include "logErrores.c"
#include "instrucciones.c"
#include "estructuras.h"

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