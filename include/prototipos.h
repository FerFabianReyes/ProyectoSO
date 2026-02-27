#ifndef prototipos
#define prototipos 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
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
void agregarToken(Renglon *renglon, Token *token);
Token* crearToken();
int agregarTipoDato(Token *token);
void liberarRenglon(Renglon *renglon);

/*---------- LÉXICO Y SINTÁCTICO --------------------------------*/
int esNumero(Token *token);
int esRegistro(Token *token);
int esInstruccion(Token *token);
int verifSintaxis(Archivo *archivo);
int parserDosParametros(Token *token);

/*---------- INSTRUCCIONES --------------------------------*/
Registros* crearRegistro();
void imprimirInstrucciones(Archivo *archivo);
void imprimirRenglon(Renglon *renglon);

/* --------- LOG ERRORES ----------------------------*/
void detectarError(int error); // Después cambiar a int para ver si hay errores o no

#endif