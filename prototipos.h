#ifndef prototipos
#define prototipos 
#include "estructuras.h"

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

/*---------- INSTRUCCIONES --------------------------------*/
Registros* crearRegistro();
void imprimirInstrucciones(Archivo *archivo);
void imprimirRenglon(Renglon *renglon);

/* --------- LOG ERRORES ----------------------------*/
void detectarError(int error);

#endif