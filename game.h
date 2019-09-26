#ifndef GAME_H
#define GAME_H
///////////////////////
/// I N C L U D E S ///
///////////////////////
/// Librerias estandar.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/// Otras librerias.
#include <time.h>
#include <ctype.h>
#include <conio.h>
/// Cabeceras.
#include "definitions.h"
#include "printers.h"
#include "utils.h"
///////////////////////////////
/// D E F I N I C I O N E S ///
///////////////////////////////
// Función encargada de la inicialización del tablero (Por defecto celdas como agua).
void gameGridInitialization( GameGrid *gameGrid, char initialization );
// Función encargada de retornar los barcos del juego.
void gameShipsInitialization( GameShips *gameShips );
// Función encargada de obtener el nombre del jugador.
void getPlayerName( char *playerName );
// Función encargada de validar si el barco está posicionado correctamente.
bool validateShipPosition( GameGrid *gameGrid, GameGridPosition *position, Orientations Orientation, bool initialPosition );
// Función encargada del posicionamiento incial de los barcos del jugador.
bool setPlayerGrid( GameGrid *playerGrid );
// Función encargada de clonar un tablero en otro.
void cloneGrid( GameGrid *destination, GameGrid *source );
// Función encargada del posicionamento de los barcos de forma aleatoria.
void setRandomGrid( GameGrid *aiGrid );
// Función encargada de validar la posición del tablero seleccionada por el jugador.
bool getPlayerShoot( GameGridPosition *position, bool *exit );
// Función encargada de controlar los disparos efectuados a un tablero a partir de una posición.
ShotTypes shootController( GameGrid *gameGrid, GameGrid *gameGridShots, GameGridPosition *position, unsigned short int *shipLenght );
// Función encargada de cambiar los barcos dañados por barcos hundidos.
void updateDamaGedShipToShunken( GameGrid *gameGridShots, GameGridPosition *position );
// Función encargada de actualizar los barcos restantes.
void updateRemainingShips( GameShips *remainingShips, unsigned short int shipSize );
// Función encargada de validar la posición aleatoria determinada por la IA.
bool validateAIPosition( GameGrid *gameGrid, GameGridPosition *position, GameShips *remainingShips );
// Función encargada de validar la dirección aleatoria determinada por la IA en el modo objetivo (antes de acertar el segundo tiro en el blanco).
bool validateAIRandomDirection( GameGrid *gameGrid, GameGridPosition *position, GameShips *remainingShips, AIShotDirections direction );
// Función encargada de rellenar de agua los laterales una vez se ha determinado la posición de tiro.
void aiWaterFill( GameGrid *shotsGrid, GameGridPosition *firstPosition, GameGridPosition *hitPosition, AIShotDirections direction, bool shunken );
// Funión encargada del control de la IA.
void aiController( GameAI *ai );
// Funión encargada de salvar el juego.
void saveGame( GameStructure *gameStructure );
// Funión encargada de validar si hay un archivo de guardado del juego.
bool hasGameSave( void );
// Funión encargada del cargar el juego.
bool loadGame( GameStructure *gameStructure );
// Funión encargada del control del juego.
void gameController( GameStructure *gameStructure, bool gameLoaded );
#endif // GAME_H
