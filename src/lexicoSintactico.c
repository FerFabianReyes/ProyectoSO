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
