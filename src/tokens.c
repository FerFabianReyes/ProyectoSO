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

int tokenizar(Archivo *archivo)
{
    if (!archivo) { return NO_HAY_ARCHIVO; }
    
    Renglon *temp = archivo->inicio;
    
    while (temp)
    {
        char *textoCopia = strdup(temp->texto);
        char *palabra, *delim;
        
        palabra = strtok_r(textoCopia, " \n\t\r", &delim);
        
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


