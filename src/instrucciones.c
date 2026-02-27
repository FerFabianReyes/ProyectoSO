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


void mov(Token *param)
{    
    Token *destino = param->sig;
    char *texto = destino->textoToken;
    if (strcmp(texto, "EAX")) { 
        if (destino->sig == REG) { 
            texto = destino->sig->textoToken;
            if (strcmp(texto, "EAX")) { reg->EAX = reg->EAX; } else
            if (strcmp(texto, "EBX")) { reg->EAX = reg->EBX; } else
            if (strcmp(texto, "ECX")) { reg->ECX = reg->ECX; }
            else { reg->EDX = reg->EDX; } 
        } 
        else {
            int num = atoi(destino->sig->textoToken);
            if (strcmp(texto, "EAX")) { reg->EAX = num; } else
            if (strcmp(texto, "EBX")) { reg->EAX = num; } else
            if (strcmp(texto, "ECX")) { reg->ECX = num; }
            else { reg->EDX = num; }
        }        
    }
}