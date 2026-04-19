#include "prototipos.h"

void detectarError(WINDOW *ventana, int error)
{
	limpiarVentana(ventana, " Errores ");
    switch (error)
    {
    case BIEN:
        break;
    /*-- Archivos --*/    
    case NOMBRE_INCORRECTO:
		mvwprintw(ventana, 2, 1, " Error %d: Archivo no encontrado. Favor de verificar el nombre", error);
        break;    
    case NO_HAY_ARCHIVO:
		mvwprintw(ventana, 2, 1, " Error %d: No se pudo abrir el archivo", error);
        break;
    case NO_HAY_TEXTO:
		mvwprintw(ventana, 2, 1, " Error %d:No se pudo leer el texto", error);
        break;   

    /*-- Léxico --*/    
    case TIPO_PARAM_INVALIDO:
		mvwprintw(ventana, 2, 1, " Error %d: Los parametros que se ingresaron son inválidos, favor de verificar", error);
        break;   
    case INICIA_MINUSCULA:
		mvwprintw(ventana, 2, 1, " Error %d: No se permiten pámetros con letras minúsculas", error);
        break;    
    case REGISTRO_INVALIDO:
		mvwprintw(ventana, 2, 1, " Error %d: Sólo se permiten registros de la A a la D sin letras munúsculas", error);
        break; 
    case NUM_DECIMAL:
		mvwprintw(ventana, 2, 1, " Error %d: No se permite ingresar números decimales", error);
        break;               
    
    /*-- Sintactico --*/   
    case INSTR_REG_INCUMPLIDA:
		mvwprintw(ventana, 2, 1, " Error %d: Revise los parámetros después de las instrucciones", error);
        break;  
    case PARAMETROS_INCORRECTOS:
		mvwprintw(ventana, 2, 1, " Error %d: Se detectaron instrucciones con parámetros incorrectos", error);
        break;   
    case PARAMETROS_INSUFICIENTES:
		mvwprintw(ventana, 2, 1, " Error %d: Se detectaron instrucciones con parámetros insuficientes", error);
        break;     
    case PARAMETROS_EXTRA:
		mvwprintw(ventana, 2, 1, " Error %d: Se detectaron instrucciones con parámetros extra", error);
        break;     
    case DIV_ENTRE_CERO:
		mvwprintw(ventana, 2, 1, " Error %d: No se puede dividir entre cero", error);
        break;  
    case ESPACIOS_EXTRA:
		mvwprintw(ventana, 2, 1, " Error %d: Se detectaron espacios múltiples en instrucciones", error);
        break;           
        
    /*-- Tokens --*/
        case NO_HAY_TOKENS: 
		mvwprintw(ventana, 2, 1, " Error %d: No se encontraron tokens", error);
        break;

    /*-- Comandos --*/
    case COMANDO_INVALIDO:
		mvwprintw(ventana, 2, 1, " Error %d: El comando que ingresó es inválido. Favor de verificar", error);
        break;
    case PROCESO_NO_ENCONTRADO:
        mvwprintw(ventana, 2, 1, " Error %d: El proceso no existe", error);
        break;    
    
    default:
        break;
    }
    wrefresh(ventana);

}
