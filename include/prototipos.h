#ifndef prototipos
#define prototipos 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <math.h>
#include <curses.h>
#include <sys/select.h>
#include "estructuras.h"
#include "enumeraciones.h"

/*---------- ARCHIVOS --------------------------------*/
Archivo* crearArchivo();
Renglon* crearRenglon(char *texto);
void agregarRenglon(Archivo *archivo, char *texto);
int imprimirArchivo(Archivo *archivo);
void liberarArchivo(Archivo *archivo);
int leerArchivo(char *nomArchivo, Archivo *archivo);
PCB* crearProceso(Archivo *prog);
void liberarProceso(PCB *proceso);

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
int espaciosMultiples(char *texto);

/*---------- INSTRUCCIONES --------------------------------*/
Registros* crearRegistro();
void imprimirInstrucciones(Archivo *archivo);
void imprimirRenglon(Renglon *renglon);
int ejecutarPrograma(PCB *proceso);
void imprimirTerminal(PCB *proceso);
char* imprimirIR(Renglon *IR);
int *obtenerRegistro(char *registro);
int mov(Token *param);
int add(Token *param);
int sub(Token *param);
int mul(Token *param);
int divR(Token *param);
int inc(Token *param);
int dec(Token *param);

/*---------- VENTANAS --------------------------------*/
int kbhit(void);
WINDOW *crearVentana(int altura, int anchura, int posY, char *nombre);
void impVentanaComandos(WINDOW *ventana);
void limpiarComando(WINDOW *ventana);
void impEncabezado(WINDOW *ventana, int maxX);
void impInstruccVentana(WINDOW *ventana, int maxX, PCB *proceso);
void limpiarVentana(WINDOW *ventana, char* nomVentana);
void impContextoEncabezado(WINDOW *ventana, int maxX);
void impContextoProceso(WINDOW *ventana, int maxX, PCB *proceso, int fila);


/*---------- COMANDOS --------------------------------*/
int detectarComando(char cad[]);
char *sacarNomArchivo(char cad[]);
void leerComando(WINDOW *ventana, int *pos, char cad[], int caracter);
void borrarCaracter(WINDOW *ventana, int *pos);
void imprimirCaracter(WINDOW *ventana, int *pos, char cad[], int caracter);
int procesarComando(char *cad, Cabecera *listos, Cabecera *vista, Ventanas *vent);

/*---------- LISTAS --------------------------------*/
Cabecera* crearCabecera();
Nodo* crearNodo(PCB *pcb);
void agregarNodo(Cabecera *cabecera, Nodo *nodo);
Nodo *sacarNodo(Cabecera *cabecera, int pid);
Nodo *buscarNodo(Cabecera *cabecera, int pid);
void imprimirLista(Cabecera *cabecera);
Nodo *desencolarNodo(Cabecera *cab);

/*---------- SIMULACIÓN --------------------------------*/
Ventanas *inicializarInterfaz();
void ejecutar(PCB *proceso, Ventanas *ventanas);
void iniciarLectura(Ventanas *ventanas, int *pos, char *cad, int *leyendo, int tamCad);
void liberarInterfaz(Ventanas *ven);
void dispatch(Cabecera *listos, Cabecera *ejecuta, Ventanas *vent);
int revisarArchivo(PCB *proceso);
void actualizarContexto(Cabecera *vista, Ventanas *ventanas);
void registrarEnVista(Cabecera *vista, Nodo *nodo);
void roundRobin(Cabecera *listos, Cabecera *ejecuta, Cabecera *terminados, Cabecera *vistaContexto, Ventanas *vent, int *cambioContexto);
void guardarRestaurarContexto(PCB *proceso, int guardar);

/* --------- LOG ERRORES ----------------------------*/
void detectarError(WINDOW *ventana, int error); 

#endif