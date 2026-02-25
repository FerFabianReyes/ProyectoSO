#include "prototipos.h"

/*--------------- Léxico ----------------------*/
int esNumero(Token *token)
{
    char *dato = token->textoToken;
    regex_t regex;
    char *patron = "^[+-]?[0-9]+$";
    char *dec = "^[+-]?[0-9]+.[0-9]?$";
    int resultado;

    resultado = regcomp(&regex, patron, REG_EXTENDED);
    resultado = regexec(&regex, dato, 0, NULL, 0);
    regfree(&regex);

    if (!resultado) { return NUM; }
    else { 
        resultado = regcomp(&regex, dec, REG_EXTENDED);
        resultado = regexec(&regex, dato, 0, NULL, 0);

        if (!resultado) { return NUM_DECIMAL; }
        else { return TIPO_PARAM_INVALIDO; }
    }
}

int esRegistro(Token *token)
{
    char *dato = token->textoToken;
    regex_t regex;
    char *patron = "^E[A-D]X$";
    char *minus = "^E[a-z]?X$";
    int resultado;

    resultado = regcomp(&regex, patron, REG_EXTENDED);
    resultado = regexec(&regex, dato, 0, NULL, 0);
    regfree(&regex);

    if (!resultado) { return REG; }
    else { 
        resultado = regcomp(&regex, minus, REG_EXTENDED);
        resultado = regexec(&regex, dato, 0, NULL, 0);

        if (!resultado) { return REGISTRO_INVALIDO; }
        else { return esNumero(token); }
    }
}

int esInstruccion(Token *token)
{
    char *dato = token->textoToken;
    regex_t regex;
    char *patron = "^(MOV|ADD|MUL|DIV|INC|DEC|END)$";
    char *minus = "^[a-z]+$";
    int resultado;

    resultado = regcomp(&regex, patron, REG_EXTENDED);
    resultado = regexec(&regex, dato, 0, NULL, 0);
    regfree(&regex);

    if (!resultado) { return INSTR; }
    else { 
        resultado = regcomp(&regex, minus, REG_EXTENDED);
        resultado = regexec(&regex, dato, 0, NULL, 0);

        if (!resultado) { return INICIA_MINUSCULA; }
        else { return esRegistro(token); }
    }
}

/*--------------- Sintáctico ----------------------*/
// Después de tokenizar
// Detectar instrucción
// Ver si se cumplen los parámetros
// Llamar a la función de esa instrucción

int parserDosParametros(Token *token)
{
    if (token->sig) {
            Token *tem = token->sig;
        if (tem->tipoParam == REG) {
            if (tem->sig) {

                if (tem->sig->sig) { return PARAMETROS_EXTRA;}

                if (!strcmp(token->textoToken, "DIV"))
                {
                    if (!strcmp(tem->sig->textoToken, "0") ||
                    !strcmp(tem->sig->textoToken, "+0") ||
                    !strcmp(tem->sig->textoToken, "-0"))
                     { return DIV_ENTRE_CERO; }
                }
                if (tem->sig->tipoParam == REG || tem->sig->tipoParam == NUM)
                { return BIEN; }
                else { return PARAMETROS_INCORRECTOS; }

            } else { return PARAMETROS_INSUFICIENTES; }
        
        } else { return INSTR_REG_INCUMPLIDA; }
    } else { return PARAMETROS_INSUFICIENTES; }
}

int parserUnParametro(Token *token)
{
    if (!token->sig)
    {
        if (token->sig->sig) { return PARAMETROS_EXTRA;}
        if (token->sig->tipoParam == REG) { return BIEN;}
        else {return TIPO_PARAM_INVALIDO;}
    } else { return PARAMETROS_INSUFICIENTES;}
}

int verifSintaxis(Archivo *archivo)
{
    if (!archivo){ return NO_HAY_ARCHIVO;}

    if (archivo->inicio) {
        Renglon *ren = archivo->inicio;
        while (ren)
        {
            if (ren->primerToken)
            {
                Token *tempTok = ren->primerToken;
                if (!strcmp(tempTok->textoToken, "MOV") || 
                !strcmp(tempTok->textoToken, "ADD") || 
                !strcmp(tempTok->textoToken, "SUB") || 
                !strcmp(tempTok->textoToken, "MUL") || 
                !strcmp(tempTok->textoToken, "DIV")) 
                {
                    int res = parserDosParametros(tempTok); 
                    printf("res: %d ", res);
                    if (res != BIEN) {return res;}
                }

                if (!strcmp(tempTok->textoToken, "INC") || 
                !strcmp(tempTok->textoToken, "DEC")) 
                {
                    int res = parserUnParametro(tempTok); 
                    printf("res: %d ", res);
                    if (res != BIEN) {return res;}
                }

                if (!strcmp(tempTok->textoToken, "END")) 
                {
                    if (tempTok->sig) { return PARAMETROS_EXTRA; }
                    printf("res: 0 ");
                }
            }
            ren = ren->sig;
        }
    } else { return NO_HAY_TEXTO; }
    return BIEN;
    
}
