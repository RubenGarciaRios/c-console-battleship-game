#ifndef PRINTERS_H
#define PRINTERS_H
///////////////////////
/// I N C L U D E S ///
///////////////////////
/// Librerías estandar.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
/// Otras librerías.
#include <conio.h>
/// Librerías Windows.
#include <Windows.h>
/// Cabeceras.
#include "definitions.h"
#include "utils.h"
///////////////////////////////
/// D E F I N I C I O N E S ///
///////////////////////////////
/// Functiones.
// Función encargada de limpiar la consola.
void clearConsole( void );
// Función encargada de obtener la posición del cursor de la consola.
void getConsoleCursorPosition( short *column, short *line );
// Función encargada de mover el cursor de la consola a la posición especificada.
void setConsoleCursorPosition( short column, short line );
// Función encargada de imprimir por pantalla con el color especificado (Dentro de los establecidos por MS).
void printStringWithColor( const char* string, int color );
// Función encargada de imprimir el mensaje especificado.
void printMessage( const char *title, const char *message, short column, short line );
// Función encargada de obligar al jugador a pulsar enter.
void printContinue( void );
// Función encargada de sacar un mensaje de confirmación por pantalla.
bool confirm( const char *title, const char *message );
// Función encargada de imprimir una barra de progreso.
void progressBar( const char* title, unsigned int progressBarwidth, unsigned int total, unsigned int current );
// Función encargada del manejo y la impresión de los errores.
void throwError( const char* string );
// Función encargada de imprimir el contenido de un fichero.
void printFileContent( const char* filePath );
// Función encargada de imprimir el tablero del juego.
void printGameGrid( GameGrid *gameGrid, short column, short line );
// Función encargada de imprimir el juego.
void printGame( GameStructure *gameStructure, bool log );
// Función encargada de imprimir los barcos restantes.
void printRemainingShips( GameShips *remainingShips );
// Función varádica, encargada de imprimir los menús del juego.
int gameMenu(
    const char* title,
    const char* description,
    const char* cursor,
    Orientations orientation,
    unsigned short int padding,
    unsigned short int defaultOption,
    unsigned short int numberOfOptions,
    ...
);
// Función encargada de imprimir los creditos del juego.
void printGameCredits( void );
#endif // PRINTERS_H
