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

extern Registros *registrosCPU;

typedef struct {
    Archivo *programa;
    int PC;
    Renglon *IR;
    Registros *regContex;
    int pid;
    int estado;
    int espera;
} PCB;

typedef struct Nodo {
    PCB *proceso;
    struct Nodo *sig;
    struct Nodo *ant;
} Nodo;

typedef struct Cabecera {
    Nodo *inicio;
    Nodo *final;
} Cabecera;

extern int nProcesos;

typedef struct
{
    WINDOW *datos;
    WINDOW *errores;
    WINDOW *comandos;
    WINDOW *contexto;
    int maxY, maxX;
} Ventanas;


#endif