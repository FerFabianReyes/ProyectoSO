#include "prototipos.h"

Token* crearToken()
{
    Token *nuevo = malloc(sizeof(Token));
    nuevo->textoToken = NULL;
    nuevo->sig = NULL;
    nuevo->tipoParam = 0;
    return nuevo;
}

void agregarToken(Renglon *renglon, Token *token)
{
    if (!renglon->primerToken) {
        renglon->primerToken = token;
    } else {
        renglon->ultimoToken->sig = token;
    }
    renglon->ultimoToken = token;
}

int agregarTipoDato(Token *token)
{    
    int tipoDato = esInstruccion(token);

    if (tipoDato == INSTR || tipoDato == REG || tipoDato == NUM)
    { 
        token->tipoParam = tipoDato;
        return BIEN;
    }
    return tipoDato;
}

void liberarRenglon(Renglon *renglon)
{
    Token *tokenActual = renglon->primerToken;
    while (tokenActual) {
        Token *tempToken = tokenActual;
        tokenActual = tokenActual->sig;
        free(tempToken->textoToken);
        free(tempToken);              
    }
    free(renglon->texto);
    free(renglon);
}

int tokenizar(Archivo *archivo)
{
    if (!archivo) { return NO_HAY_ARCHIVO; }
    
    Renglon *temp = archivo->inicio;
    Renglon *ant = NULL;

    while (temp)
    {
        char *textoCopia = strdup(temp->texto);
        char *palabra, *delim;
        
        palabra = strtok_r(textoCopia, " \n\t\r", &delim);
        
        if (!palabra)
        {
            Renglon *elimin = temp;
            temp = temp->sig;
 
            if (ant == NULL) { archivo->inicio = temp; } 
            else { ant->sig = temp; }
            
            if (elimin == archivo->final) { archivo->final = ant; }
            
            archivo->tamanio--;
            liberarRenglon(elimin);
            free(textoCopia);
            continue;
        }
        
        while (palabra)
        {   
            Token *nuevoToken = crearToken();
            nuevoToken->textoToken = strdup(palabra);

            int res = agregarTipoDato(nuevoToken);
            if (res == BIEN) { agregarToken(temp, nuevoToken); } 
            else { 
                free(nuevoToken->textoToken);
                free(nuevoToken);  free(textoCopia);
                return res; 
            }
            palabra = strtok_r(NULL, " \n\t\r", &delim);
        }
        free(textoCopia);
        ant = temp; 
        temp = temp->sig;
    }
    
    return BIEN;
}

int imprimirTokens(Archivo *archivo)
{
    if (!archivo){ return NO_HAY_ARCHIVO;}
    Renglon *temp = archivo->inicio;
    while (temp)
    {
        Token *tempTok = temp->primerToken;

        while (tempTok)
        {
            printf("token: %s", tempTok->textoToken);
            printf("tipo: %d", tempTok->tipoParam);
            tempTok = tempTok->sig;
        }
        temp = temp->sig;
    }
    return BIEN;
}


