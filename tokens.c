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

/*int limpiarToken(Token *token)
{
    int i = 0;
    while (token->textoToken[i])
    {
        if ((token->textoToken[i] == '\n') || (token->textoToken[i] == ' ')) {
            token->textoToken[i] = '\0';
            break;
        }
        i++;
    }
}*/

int tokenizar(Archivo *archivo)
{
    Renglon *temp = archivo->inicio;

    while (temp)
    {
        char *palabra, *delim;
        palabra = strtok_r(temp->texto, " ", &delim);
        while (palabra)
        {
            Token *nuevoToken = crearToken();
            nuevoToken->textoToken = palabra;
           // limpiarToken(nuevoToken);
            agregarToken(temp, nuevoToken);
            palabra = strtok_r(NULL, " ", &delim);
        }
        temp = temp->sig;
    }
}

int imprimirTokens(Archivo *archivo)
{
    Renglon *temp = archivo->inicio;

    while (temp)
    {
        Token *tempTok = temp->primerToken;
        while (tempTok)
        {
            printf("token:%s", tempTok->textoToken);
            tempTok = tempTok->sig;
        }
        temp = temp->sig;
    }
    
}


