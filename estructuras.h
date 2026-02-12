#ifndef estructura
#define estructura 

typedef struct
{
    char *instruccion;
    char *elResto;
} Tokens;

typedef struct Renglon{
    char *texto;
    struct Renglon *sig;
    Tokens *tokens;
} Renglon;

typedef struct {
    Renglon *inicio;
    Renglon *final;
    int tamanio;
} Archivo;

/*Se pondrán retornos de entero para detectar errores
tal vez el inicio de cada número indica el tipo de error
como en los tintes que dicen el subtono*/
Archivo* crearArchivo();
Renglon* crearRenglon(char *texto);
void agregarRenglon(Archivo *archivo, char *texto);
void imprimirArchivo(Archivo *archivo);
void imprimirRenglon(int renglon, Archivo *archivo);
void liberarArchivo(Archivo *archivo);
int leerArchivo(char *nomArchivo, Archivo *archivo);
int limpiarRenglones(Archivo **archivo);
void imprimirTokens(Archivo *archivo);

#endif