#include "prototipos.h"

void detectarError(int error)
{
    switch (error)
    {
    case BIEN:
        break;
    /*-- Archivos --*/    
    case NOMBRE_INCORRECTO:
        printf("Error %d: Archivo no encontrado. Favor de verificar el nombre", error);
        break;    
    case NO_HAY_ARCHIVO:
        printf("Error %d: No se pudo abrir el archivo", error);
        break;
    case NO_HAY_TEXTO:
        printf("Error %d: No se pudo leer el texto", error);
        break;   

    /*-- Léxico --*/    
    case TIPO_PARAM_INVALIDO:
        printf("Error %d: Los parametros que se ingresaron son inválidos, favor de verificar", error);
        break;   
    case INICIA_MINUSCULA:
        printf("Error %d: No se permiten pámetros con letras minúsculas", error);
        break;    
    case REGISTRO_INVALIDO:
        printf("Error %d: Sólo se permiten registros de la A a la D sin letras munúsculas", error);
        break; 
    case NUM_DECIMAL:
        printf("Error %d: No se permite ingresar números decimales", error);
        break;               
    
    /*-- Sintactico --*/   
    case INSTR_REG_INCUMPLIDA:
        printf("Error %d: Después de una instrucción MOV, ADD, MULL... debe de seguir un registro", error);
        break;  
    case PARAMETROS_INCORRECTOS:
        printf("Error %d: Se detectaron instrucciones con parámetros incorrectos", error);
        break;   
    case PARAMETROS_INSUFICIENTES:
        printf("Error %d: Se detectaron instrucciones con parámetros insuficientes", error);
        break;     
    case PARAMETROS_EXTRA:
        printf("Error %d: Se detectaron instrucciones con parámetros extra", error);
        break;     
        
    /*-- Tokens --*/
        case NO_HAY_TOKENS: 
        printf("Error %d: No se encontraron tokens.", error);
        break;
    default:
        break;
    }
}
