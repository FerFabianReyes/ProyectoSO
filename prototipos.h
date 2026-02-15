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

// todo bien = 0
/*------------ ERRORES Y ADVERTENCIAS ---------------------------------*/ 
enum errorArchivo {
    /*-- Errores --*/
    NOMBRE_INCORRECTO = 1000,
    NO_HAY_ARCHIVO,
    NO_HAY_TEXTO,

    /*-- Advertencias*/
    SALTO_LINEA_EXTRA = 1500,
    ESPACIO_EXTRA
};

enum errorToken {
    /*-- Errores --*/
    NO_HAY_TOKENS = 2000,

    /*-- Advertencias*/

};


/*---------- ARCHIVOS --------------------------------*/
Archivo* crearArchivo();
Renglon* crearRenglon(char *texto);
void agregarRenglon(Archivo *archivo, char *texto);
int imprimirArchivo(Archivo *archivo);
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