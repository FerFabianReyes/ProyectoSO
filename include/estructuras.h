#ifndef estructuras
#define estructuras 

typedef struct Token{
    char *textoToken;
    int tipoParam;
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

typedef struct {
    int EAX;    int EBX;
    int ECX;    int EDX;
}Registros;

/*------------ TIPO DE PARAMETRO  ---------------------------------*/ 
typedef enum {
    INSTR = 1, REG, NUM
} tipoParametro;

/*------------ TIPO DE INSTRUCCION  ---------------------------------*/ 
typedef enum {
    MOV = 10,    ADD,
    MUL,        DIV,
    INC,        DEC,
    END
}tipoInstruccion;

/*------------ ERRORES Y ADVERTENCIAS ---------------------------------*/ 
typedef enum {
    BIEN = 0,
/*----- Archivos -----*/ 
    // Errores
    NOMBRE_INCORRECTO = 100,
    NO_HAY_ARCHIVO,
    NO_HAY_TEXTO,

/*----- Lexico -----*/ 
    // Errores
    INICIA_EN_NUMERO = 300,
    TIPO_PARAM_INVALIDO,
    INICIA_MINUSCULA,
    REGISTRO_INVALIDO,
    NUM_DECIMAL,

/*----- Sintáctico -----*/ 
     // Erroes
    PARAMETROS_INSUFICIENTES = 400,
    PARAMETROS_EXTRA,
    PARAMETROS_INCORRECTOS,

    //Advertencias
    ESPACIOS_EXTRA = 450,
    SALTOS_LINEA_EXTRA,

/*----- Tokens -----*/ 
    //Errores
    NO_HAY_TOKENS = 200,
} errorAdvertencia;

#endif