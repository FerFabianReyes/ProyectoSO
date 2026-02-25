#include "prototipos.h"

Registros* crearRegistro()
{
    Registros *nuevo = malloc(sizeof(Registros));
    nuevo->EAX = 0;    nuevo->EBX = 0;
    nuevo->ECX = 0;    nuevo->EDX = 0;
    return nuevo;
}

void imprimirRenglon(Renglon *renglon)
{
    if (renglon->primerToken)
    {
        Token *tempTok = renglon->primerToken;
        int i;
        while (tempTok)
        {
            printf("%s ", tempTok->textoToken);
          //  printf("tipoParam: %d ", tempTok->tipoParam);
            tempTok = tempTok->sig;
            i++;
        }
        printf("\n");
    }
}

void imprimirInstrucciones(Archivo *archivo)
{
    Renglon *tempRen = archivo->inicio;
    int i = 0;
    printf("\n ____________________\n");
    printf("|   INSTRUCCIONES   |\n");
    printf("---------------------\n");

    while (tempRen)
    {
        imprimirRenglon(tempRen);
        tempRen = tempRen->sig;
    }
}

/*
Primero ver el orden de la cadena
void mov(Token *var)
{    
    Token *sig = var->sig;
    char *texto = sig->textoToken;
    if (sig->tipoParam == REG)
    {
        
    } else
    {
        int num = texto - '0';
        if (var->textoToken == "MOV")
        {
            
        }
    }

}*/