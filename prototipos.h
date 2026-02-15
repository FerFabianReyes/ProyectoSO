#ifndef prototipos
#define prototipos 

typedef struct Token{
    char *textoToken;
    struct Token *sig;
} Token;

typedef struct Renglon{
    char *texto;
    struct Renglon *sig;
    Token *primerToken;
    Token *ultimoToken;
} Renglon;

typedef struct {
    Renglon *inicio;
    Renglon *final;
    int tamanio;
} Archivo;

/*Se pondrán retornos de entero para detectar errores
tal vez el inicio de cada número indica el tipo de error
como en los tintes que dicen el subtono*/

/*---------- ARCHIVOS --------------------------------*/
Archivo* crearArchivo();
Renglon* crearRenglon(char *texto);
void agregarRenglon(Archivo *archivo, char *texto);
void imprimirArchivo(Archivo *archivo);
void imprimirRenglon(int renglon, Archivo *archivo);
void liberarArchivo(Archivo *archivo);
int leerArchivo(char *nomArchivo, Archivo *archivo);

/*---------- TOKENS --------------------------------*/
int tokenizar(Archivo *archivo);
int imprimirTokens(Archivo *archivo);
int agregarToken(Renglon *renglon, Token *token);
Token* crearToken();
int limpiarToken(Token *token);



#endif