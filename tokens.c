Token* crearToken()
{
    Token *nuevo = malloc(sizeof(Token));
    nuevo->textoToken = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

int agregarToken(Renglon *renglon, Token *token)
{
    if (!renglon->primerToken) {
        renglon->primerToken = token;
    } else {
        renglon->ultimoToken->sig = token;
    }
    renglon->ultimoToken = token;
}

int tokenizar(Archivo *archivo)
{
    Renglon *temp = archivo->inicio;
    if (!archivo){ return NO_HAY_ARCHIVO;}
    
    while (temp)
    {
        char *textoCopia = strdup(temp->texto);
        char *palabra, *delim;
        palabra = strtok_r(textoCopia, ", \n\t\r", &delim);
        
        while (palabra)
        {   
            Token *nuevoToken = crearToken();
            nuevoToken->textoToken = strdup(palabra);
            agregarToken(temp, nuevoToken);
            
            palabra = strtok_r(NULL, ", \n\t\r", &delim);
        }
        free(textoCopia); 
        temp = temp->sig;
    }
    return 0;
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
            tempTok = tempTok->sig;
        }
        temp = temp->sig;
    }
}


