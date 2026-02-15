
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

void imprimirArchivo(Archivo *archivo)
{
    if (archivo->inicio) {
        Renglon *temp = archivo->inicio;
        while (temp)
        {
            printf("%s", temp->texto);
            temp = temp->sig;
        }
    } else { printf("No hay texto"); }
}

void imprimirRenglon(int renglon, Archivo *archivo)
{
    if (renglon > archivo->tamanio-1) 
    { printf("Máximo de renglones: %d\nEl índice empieza en 0\n", archivo->tamanio); }
    else {
        Renglon *temp = archivo->inicio;
        for (int i = 0; i < renglon; i++) { temp = temp->sig; }
        printf("%s", temp->texto);
    }
}

void liberarArchivo(Archivo *archivo)
{
    Renglon *actual = archivo->inicio;
    while (actual) {
        Renglon *temp = actual;
        actual = actual->sig;
        free(temp->texto);
        free(temp);
    }
    free(archivo);
}

int leerArchivo(char *nomArchivo, Archivo *archivo)
{
    char *ren = NULL;
    size_t tamanio = 0;
    ssize_t caracteres;

    FILE *arch = fopen(nomArchivo, "r");
    if (arch == NULL) { printf("No se encontrón el archivo\n"); return 0; }

    while ((caracteres = getline(&ren, &tamanio, arch)) != -1)
    {
       agregarRenglon(archivo, ren);
    }   

    fclose(arch);
    free(ren);
    return 1;
}
