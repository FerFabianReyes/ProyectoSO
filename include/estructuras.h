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

extern Registros *reg;

typedef struct {
    Archivo *programa;
    int PC;
    Renglon *IR;
    int estado;
    int espera;
} Proceso;

#endif