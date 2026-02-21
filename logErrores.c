void detectarError(int error)
{
    switch (error)
    {
    case 0:
        break;
    /*-- Archivos --*/    
    case NOMBRE_INCORRECTO:
        printf("Error %d: Archivo no encontrado. Favor de verificar el nombre", error);
        break;    
    case NO_HAY_ARCHIVO:
        printf("Error %d: No se pudo abrir el archivo.", error);
        break;
    case NO_HAY_TEXTO:
        printf("Error %d: No se pudo leer el texto", error);
        break;    
    /*-- Léxico --*/    
    case INICIA_EN_NUMERO:
        printf("Error %d: No se permite que instrucciones o variables que empiecen con un número.", error);
        break;
    case TIENE_MINUSCULA:
        printf("Error %d: No se permite que instrucciones tengan letras minúsculas.", error);
        break;   
    case CARACTERES_ESPECIALES:
        printf("Error %d: No se permite que instrucciones o variables que empiecen con un número.", error);
        break;
    /*-- Sintactico --*/   
     case PARAMETROS_INSUFICIENTES:
        printf("Error %d: Se detectaron instrucciones con parámetros insuficientes", error);
        break;
    case PARAMETROS_EXTRA:
        printf("Error %d: Se detectaron instrucciones con parámetros extra", error);
        break;     
    case PARAMETROS_INCORRECTOS:
        printf("Error %d: Se detectaron instrucciones con parámetros incorrectos", error);
        break;
    /*-- Tokens --*/
        printf("Error %d: No se encontraron tokens.", error);
        break;
    default:
        break;
    }
}
