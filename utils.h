#ifndef UTILS_H
#define UTILS_H
///////////////////////
/// I N C L U D E S ///
///////////////////////
/// Librerias estandar.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
/// Otras librerias.
#include <conio.h>
/// Cabeceras.
#include "definitions.h"
///////////////////////////////
/// D E F I N I C I O N E S ///
///////////////////////////////
// Función encargada de concatenar cadenas en un string resultante.
const char* concatenate( const char* stringA, const char* stringB );
// Función encargada de retornar un string a partir de un tipo char.
char* charToString( const char c );
// Función encargada de quitar los espacios de la parte izquierda de un string.
char *leftTrim( char *string );
// Función encargada de quitar los espacios de la parte derecha de un string.
char *rightTrim( char *string );
// Función encargada de quitar los espacios de un string.
char *trim( char *string );
// Función encargada de imprimir por consola y pausar la ejecución hasta que se introduzca una tecla.
void consoleLog( const char *message );
#endif // UTILS_H
