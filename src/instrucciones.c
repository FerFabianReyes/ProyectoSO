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

int ejecutarPrograma(Ejecucion *ejec)
{
    if (!strcmp(ejec->IR->primerToken->textoToken, "MOV")){
        ejec->PC++;
       return mov(ejec->IR->primerToken);
    }

    if (!strcmp(ejec->IR->primerToken->textoToken, "ADD")){
        ejec->PC++;
        return add(ejec->IR->primerToken);
    }

    if (!strcmp(ejec->IR->primerToken->textoToken, "SUB")){
        ejec->PC++;
        return sub(ejec->IR->primerToken);
    }

    if (!strcmp(ejec->IR->primerToken->textoToken, "MUL")){
        ejec->PC++;
        return mul(ejec->IR->primerToken);
    }

    if (!strcmp(ejec->IR->primerToken->textoToken, "DIV")){
        ejec->PC++;
        return divR(ejec->IR->primerToken);
    }

    if (!strcmp(ejec->IR->primerToken->textoToken, "INC")){
        ejec->PC++;
        return inc(ejec->IR->primerToken);
    }

    if (!strcmp(ejec->IR->primerToken->textoToken, "DEC")){
        ejec->PC++;
        return dec(ejec->IR->primerToken);
    }

    if (!strcmp(ejec->IR->primerToken->textoToken, "END")){
        ejec->PC++;
        return BIEN;
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

int *obtenerRegistro(char *registro)
{
    if (!strcmp(registro, "EAX")) { return &reg->EAX; }
    if (!strcmp(registro, "EBX")) { return &reg->EBX; }
    if (!strcmp(registro, "ECX")) { return &reg->ECX; }
    if (!strcmp(registro, "EDX")) { return &reg->EDX; }    
}

int mov(Token *param)
{    
    int *regDestino = obtenerRegistro(param->sig->textoToken);
    if (param->sig->sig->tipoParam == REG) {
        int *regValor = obtenerRegistro(param->sig->sig->textoToken);
        *regDestino = *regValor;
    } else {
        int num = atoi(param->sig->sig->textoToken);
        *regDestino = num;
    }
    return BIEN;
}

int add(Token *param)
{    
    int *regDestino = obtenerRegistro(param->sig->textoToken);
    if (param->sig->sig->tipoParam == REG) {
        int *regValor = obtenerRegistro(param->sig->sig->textoToken);
        *regDestino = *regDestino + *regValor;
    } else {
        int num = atoi(param->sig->sig->textoToken);
        *regDestino = *regDestino + num;
    }
    return BIEN;
}

int sub(Token *param)
{    
    int *regDestino = obtenerRegistro(param->sig->textoToken);
    if (param->sig->sig->tipoParam == REG) {
        int *regValor = obtenerRegistro(param->sig->sig->textoToken);
        *regDestino = *regDestino - *regValor;
    } else {
        int num = atoi(param->sig->sig->textoToken);
        *regDestino = *regDestino - num;
    }
    return BIEN;
}

int mul(Token *param)
{    
    int *regDestino = obtenerRegistro(param->sig->textoToken);
    if (param->sig->sig->tipoParam == REG) {
        int *regValor = obtenerRegistro(param->sig->sig->textoToken);
        *regDestino = *regDestino * *regValor;
    } else {
        int num = atoi(param->sig->sig->textoToken);
        *regDestino = *regDestino * num;
    }
    return BIEN;
}

int divR(Token *param)
{    
    int *regDestino = obtenerRegistro(param->sig->textoToken);
    if (param->sig->sig->tipoParam == REG) {
        int *regValor = obtenerRegistro(param->sig->sig->textoToken);
        if (!(*regValor)) { return DIV_ENTRE_CERO; }
        *regDestino = (int)floor((double)*regDestino / *regValor);
    } else {
        int num = atoi(param->sig->sig->textoToken);
        *regDestino = (int)floor((double)*regDestino / num);
    }
    return BIEN;
}

int inc(Token *param)
{    
    int *regDestino = obtenerRegistro(param->sig->textoToken);
    *regDestino = *regDestino + 1;
    return BIEN;
}

int dec(Token *param)
{    
    int *regDestino = obtenerRegistro(param->sig->textoToken);
    *regDestino = *regDestino - 1;
    return BIEN;

}