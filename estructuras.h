#ifndef estructuras
#define estructuras 

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

/*------------ TIPO DE INSTRUCCION  ---------------------------------*/ 
enum tipoInstruccion {
    MOV = 1,    ADD,
    MUL,        DIV,
    INC,        DEC,
    END
}

/*------------ ERRORES Y ADVERTENCIAS ---------------------------------*/ 
// todo bien = 0
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


#endif