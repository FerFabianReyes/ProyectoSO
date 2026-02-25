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
    return 0;
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
