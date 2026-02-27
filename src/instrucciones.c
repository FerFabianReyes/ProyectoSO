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

void ejecutarPrograma(Ejecucion *ejec)
{
    if (!strcmp(ejec->IR->primerToken->textoToken, "MOV")){
        mov(ejec->IR->primerToken);
        ejec->PC++;
    }
}

char* imprimirIR(Renglon *IR)
{
    Token *tokenAct = IR->primerToken;
    char *cadena = malloc(1);
    cadena[0] = '\0';
    while (tokenAct)
    {
        cadena = realloc(cadena, strlen(cadena) + strlen(tokenAct->textoToken) + 2);
        strcat(cadena, tokenAct->textoToken);
        strcat(cadena, " ");
        tokenAct = tokenAct->sig;
    }
    return cadena;
}

void imprimirTerminal(Ejecucion *ejec)
{
    printf("\n_______________________________________________________\n");
    printf("PC\tIR\t\tEAX\tEBX\tECX\tEDX");
    printf("\n--------------------------------------------------------\n");
    printf("%d\t%s\t%d\t%d\t%d\t%d", ejec->PC, imprimirIR(ejec->IR), reg->EAX,reg->EBX, reg->ECX, reg->EDX);
    printf("\n");
}



void mov(Token *param)
{    
    Token *destino = param->sig;
    char *texto = destino->textoToken;
    if (!strcmp(texto, "EAX")) { 
        texto = destino->sig->textoToken;
        if (destino->sig->tipoParam == REG) { 
            if (!strcmp(texto, "EAX")) { reg->EAX = reg->EAX; } else
            if (!strcmp(texto, "EBX")) { reg->EAX = reg->EBX; } else
            if (!strcmp(texto, "ECX")) { reg->EAX = reg->ECX; }
            else { reg->EAX = reg->EDX; } 
        } 
        else {
            int num = atoi(destino->sig->textoToken);
            reg->EAX = num;
        }        
    }

    if (!strcmp(texto, "EBX")) { 
        texto = destino->sig->textoToken;
        if (destino->sig->tipoParam == REG) { 
            if (!strcmp(texto, "EAX")) { reg->EBX = reg->EAX; } else
            if (!strcmp(texto, "EBX")) { reg->EBX = reg->EBX; } else
            if (!strcmp(texto, "ECX")) { reg->EBX = reg->ECX; }
            else { reg->EBX = reg->EDX; } 
        } 
        else {
            int num = atoi(destino->sig->textoToken);
            reg->EBX = num;
        }     
    }

    if (!strcmp(texto, "ECX")) { 
        texto = destino->sig->textoToken;
        if (destino->sig->tipoParam == REG) { 
            if (!strcmp(texto, "EAX")) { reg->ECX = reg->EAX; } else
            if (!strcmp(texto, "EBX")) { reg->ECX = reg->EBX; } else
            if (!strcmp(texto, "ECX")) { reg->ECX = reg->ECX; }
            else { reg->ECX = reg->EDX; } 
        } 
        else {
            int num = atoi(destino->sig->textoToken);
            reg->ECX = num;
        }        
    }

    if (!strcmp(texto, "EDX")) { 
        texto = destino->sig->textoToken;
        if (destino->sig->tipoParam == REG) { 
            if (!strcmp(texto, "EAX")) { reg->EDX = reg->EAX; } else
            if (!strcmp(texto, "EBX")) { reg->EDX = reg->EBX; } else
            if (!strcmp(texto, "ECX")) { reg->EDX = reg->ECX; }
            else { reg->EDX = reg->EDX; } 
        } 
        else {
            int num = atoi(destino->sig->textoToken);
            reg->EDX = num;
        }        
    }
}