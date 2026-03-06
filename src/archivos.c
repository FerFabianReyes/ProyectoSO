#include "prototipos.h"

Ejecucion* crearEjecucion(Archivo *prog)
{
    Ejecucion *nueva = malloc(sizeof(Ejecucion));
    nueva->programa = prog;
    nueva->PC = -1;
    nueva->IR = prog->inicio;
    nueva->estado = ESPERA;
    nueva->espera = 0;
    reg->EAX = 0; reg->EBX = 0; reg->ECX = 0; reg->EDX = 0;
    return nueva;
}

Archivo* crearArchivo()
{
    Archivo *nuevo = malloc(sizeof(Archivo));
    nuevo->final = NULL;
    nuevo->inicio = NULL;
    nuevo->tamanio = 0;
    return nuevo;
}

Renglon* crearRenglon(char *texto)
{
    Renglon *nuevo = malloc(sizeof(Renglon));
    nuevo->texto = strdup(texto);
    nuevo->sig = NULL;
    nuevo->primerToken = NULL;
    nuevo->ultimoToken = NULL;

    return nuevo;
}

void agregarRenglon(Archivo *archivo, char *texto)
{
    Renglon *nuevo = crearRenglon(texto);
    if (archivo->final) {
        archivo->final->sig = nuevo;
    } else {
        archivo->inicio = nuevo;
    }
    archivo->final = nuevo;
    archivo->tamanio++;
}

int imprimirArchivo(Archivo *archivo)
{
    if (!archivo){ return NO_HAY_ARCHIVO;}
    
    if (archivo->inicio) {
        Renglon *temp = archivo->inicio;
        while (temp)
        {
            printf("%s", temp->texto);
            temp = temp->sig;
        }
    } else { return NO_HAY_TEXTO; }
    return BIEN;
}

void liberarArchivo(Archivo *archivo)
{
    Renglon *actualRenglon = archivo->inicio;
    
    while (actualRenglon) {
        Token *actualToken = actualRenglon->primerToken;
        while (actualToken) {
            Token *tempToken = actualToken;
            actualToken = actualToken->sig;
            
            free(tempToken->textoToken);  
            free(tempToken); 
        }
        
        Renglon *tempRenglon = actualRenglon;
        actualRenglon = actualRenglon->sig;
        free(tempRenglon->texto);  
        free(tempRenglon);
    }
    
    free(archivo); 
}

void liberarEjecucion(Ejecucion *ejec)
{
    if (!ejec) { return; }
    liberarArchivo(ejec->programa);
    ejec->programa = NULL;
    ejec->IR = NULL;
    free(ejec);
}

int leerArchivo(char *nomArchivo, Archivo *archivo)
{
    if (!archivo){ return NO_HAY_ARCHIVO;}

    char *ren = NULL;
    size_t tamanio = 0;
    ssize_t caracteres;

    FILE *arch = fopen(nomArchivo, "r");
    if (arch == NULL) { return NOMBRE_INCORRECTO; }

    while ((caracteres = getline(&ren, &tamanio, arch)) != -1)
    {
       agregarRenglon(archivo, ren);
    }   

    fclose(arch);
    free(ren);
    return BIEN;
}
