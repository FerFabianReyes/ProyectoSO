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
    NOMBRE_INCORRECTO = 100,
    NO_HAY_ARCHIVO,
    NO_HAY_TEXTO
};

enum errorLexico {
    /*-- Errores --*/
    INICIA_EN_NUMERO = 300,
    TIENE_MINUSCULA,
    CARACTERES_ESPECIALES
};

enum errorSintactico {
    /*-- Errores --*/
    PARAMETROS_INSUFICIENTES = 400,
    PARAMETROS_EXTRA,
    PARAMETROS_INCORRECTOS,

    /*-- Advertencias --*/
    ESPACIOS_EXTRA = 450,
    SALTOS_LINEA_EXTRA
};

enum errorToken {
    /*-- Errores --*/
    NO_HAY_TOKENS = 200,
};


/*---------- ARCHIVOS --------------------------------*/
Archivo* crearArchivo();
Renglon* crearRenglon(char *texto);
void agregarRenglon(Archivo *archivo, char *texto);
int imprimirArchivo(Archivo *archivo);
void liberarArchivo(Archivo *archivo);
int leerArchivo(char *nomArchivo, Archivo *archivo);

/*---------- TOKENS --------------------------------*/
int tokenizar(Archivo *archivo);
int imprimirTokens(Archivo *archivo);
int agregarToken(Renglon *renglon, Token *token);
Token* crearToken();
int limpiarToken(Token *token);

/* --------- LOG ERRORES ----------------------------*/
void detectarError(int error);
void imprimirRenglon(int indice, Renglon *renglon);
void imprimirInstrucciones(Archivo *archivo);


#endif