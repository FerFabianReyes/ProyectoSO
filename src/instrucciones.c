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

int ejecutarPrograma(Proceso *proceso)
{
    if (!strcmp(proceso->IR->primerToken->textoToken, "MOV")){
        proceso->PC++;
       return mov(proceso->IR->primerToken);
    }

    if (!strcmp(proceso->IR->primerToken->textoToken, "ADD")){
        proceso->PC++;
        return add(proceso->IR->primerToken);
    }

    if (!strcmp(proceso->IR->primerToken->textoToken, "SUB")){
        proceso->PC++;
        return sub(proceso->IR->primerToken);
    }

    if (!strcmp(proceso->IR->primerToken->textoToken, "MUL")){
        proceso->PC++;
        return mul(proceso->IR->primerToken);
    }

    if (!strcmp(proceso->IR->primerToken->textoToken, "DIV")){
        proceso->PC++;
        return divR(proceso->IR->primerToken);
    }

    if (!strcmp(proceso->IR->primerToken->textoToken, "INC")){
        proceso->PC++;
        return inc(proceso->IR->primerToken);
    }

    if (!strcmp(proceso->IR->primerToken->textoToken, "DEC")){
        proceso->PC++;
        return dec(proceso->IR->primerToken);
    }

    if (!strcmp(proceso->IR->primerToken->textoToken, "END")){
        proceso->PC++;
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

void imprimirTerminal(Proceso *proceso)
{
    printf("\n_______________________________________________________\n");
    printf("PC\tIR\t\tEAX\tEBX\tECX\tEDX");
    printf("\n--------------------------------------------------------\n");
    printf("%d\t%s\t%d\t%d\t%d\t%d", proceso->PC, imprimirIR(proceso->IR), reg->EAX,reg->EBX, reg->ECX, reg->EDX);
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