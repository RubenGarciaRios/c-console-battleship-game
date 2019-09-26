#ifndef DEFINITIONS_H
#define DEFINITIONS_H
///////////////////////
/// I N C L U D E S ///
///////////////////////
/// Librerias estandar.
#include <stdbool.h>
///////////////////////////////
/// D E F I N I C I O N E S ///
///////////////////////////////
// PATHS.
#define GAMESAVE_FILE_DIRECTORY         "./"
#define TEMPLATE_FILES_DIRECTORY        "./templates/"
// GRID.
#define GAME_GRID_ROWS                  10
#define GAME_GRID_COLS                  10
#define GAME_GRID_ROWS_ENUMERATION      "ABCDEFGHIJ"
#define GAME_GRID_COLS_ENUMERATION      "0123456789"
#define GAME_GRID_NULL                  '-'
#define GAME_GRID_WATER                 'A'
#define GAME_GRID_SHIP                  'B'
#define GAME_GRID_DAMAGED               'X'
#define GAME_GRID_SHUNKEN               'H'
#define GAME_GRID_WRONG_POSITION        '#'
#define GAME_GRID_AI_MISS               '@'
// COLORES.
#define GAME_COLOR_RED                  0x04
#define GAME_COLOR_GREEN                0x02
#define GAME_COLOR_BLUE                 0x03
#define GAME_LIGHT_COLOR_RED            0x0C
#define GAME_COLOR_DARK_BLUE            0x01
#define GAME_COLOR_LIGHT_BLUE           0x0B
#define GAME_COLOR_LIGHT_GREEN          0x0A
#define GAME_COLOR_GRAY                 0x0B
#define GAME_COLOR_YELLOW               0x0E
// BARCOS.
#define GAME_SHIPS_TYPES                4
#define GAME_SHIPS_PROPERTIES           2
#define GAME_SHIP_TOTAL_COUNT           10
#define GAME_SHIP_BATTLESHIP_SPACING    4
#define GAME_SHIP_BATTLESHIP_COUNT      1
#define GAME_SHIP_CRUISER_SPACING       3
#define GAME_SHIP_CRUISER_COUNT         2
#define GAME_SHIP_SUBMARINE_SPACING     2
#define GAME_SHIP_SUBMARINE_COUNT       3
#define GAME_SHIP_DESTROYER_SPACING     1
#define GAME_SHIP_DESTROYER_COUNT       4
//ERRORES.
#define GAME_ERROR_FILE_NOT_FOUND       "Error. No se ha encontrado el fichero especificado."
#define GAME_ERROR_INVALID_MENU_OPTION  "Error. La opcion seleccionada, no esta contemplada por el juego."
#define GAME_ERROR_INVALID_SHIP         "Error. El barco seleccionado, no esta contemplado por el juego."
#define GAME_ERROR_UNABLE_TO_SAVE_GAME  "Error. No se ha podido guardar el juego."
// OTROS.
#define GAME_MENU_RETURN                -1
#define GAME_PLAYER_NAME_MAX_LENGHT     21
#define GAMESAVE_FILE_NAME              "gamesave"
/////////////////////////////////////
/// T I P O S   D E F I N I D O S ///
/////////////////////////////////////
// Definición de las fases del juego.
typedef enum
    { GAME_INITIALIZATION,
      PLAYER_SHIPS_ALLOCATION,
      AI_SHIPS_ALLOCATION,
      GAME_STARTS,
      PLAYER_SHOOT,
      AI_SHOOT } GamePhases;
// Definición de los tipos de orientación.
typedef enum
    { HORIZONTAL, VERTICAL } Orientations;
// Definición de los tipos de barcos que hay en el juego.
typedef enum
    { BATTLESHIP, CRUISER, SUBMARINE, DESTROYER } ShipTypes;
// Definición de los tipos de tiros que hay en el juego.
// - Agua, tocado y hundido.
typedef enum
    { SHOT_MISS, SHOT_HIT, SHOT_SUNKEN, SHOT_INVALID } ShotTypes;
// Definición de los estados / modos de la IA.
typedef enum
    { HUNT_MODE, TARGET_MODE } AIModes;
// Definición de las posibles direcciones de los tiros de la IA.
typedef enum
    { DIRECTION_TOP, DIRECTION_LEFT, DIRECTION_BOTTOM, DIRECTION_RIGHT, DIRECTION_NULL } AIShotDirections;
// Definición del código de las teclas usadas en el juego.
typedef enum
    { KEYCODE_ENTER = 0x0D,
      KEYCODE_ESC   = 0x1B,
      KEYCODE_UP    = 0x48,
      KEYCODE_RIGHT = 0x4D,
      KEYCODE_DOWN  = 0x50,
      KEYCODE_LEFT  = 0x4B,
      KEYCODE_W     = 0x77,
      KEYCODE_A     = 0x61,
      KEYCODE_S     = 0x73,
      KEYCODE_D     = 0x64,
      KEYCODE_N     = 0x6E,
      KEYCODE_R     = 0x72 } KeyCodes;
// Definición de los acentos para mostrar en la salidas.
typedef enum
    { LOWERCASE_A = 160,
      LOWERCASE_E = 130,
      LOWERCASE_I = 161,
      LOWERCASE_O = 162,
      LOWERCASE_U = 163,
      LOWERCASE_N = 164,
      UPPERCASE_A = 181,
      UPPERCASE_E = 144,
      UPPERCASE_I = 214,
      UPPERCASE_O = 224,
      UPPERCASE_U = 23,
      UPPERCASE_N = 165 } OrthographicAccents;
// Definición de las opciones principales del juego.
typedef enum
    { GAME_START            = 1,
      GAME_LOAD_GAME        = 2,
      GAME_OPTIONS          = 3,
      GAME_CREDITS          = 4,
      GAME_EXIT             = 5,
      GAME_MAIN_MENU_RETURN = GAME_MENU_RETURN } GameMainMenuOptions;
// Definición de las opciones principales del juego.
typedef enum
    { TOGGLE_GAME_DEBUG_MODE     = 1,
      TOGGLE_PLAYER_SHIPS_RANDOM = 2,
      GAME_OPTIONS_MENU_RETURN   = GAME_MENU_RETURN } GameOptionsMenuOptions;
// Definición del tablero del juego.
typedef char GameGrid[ GAME_GRID_COLS ][ GAME_GRID_ROWS ];
// Definición de las propiedades de los barcos:
// - La primera dimensión indica el tipo de barco que es en relación con la enumeración de ShipTipes.
// - La segunda dimensión indica el número de barcos disponibles, y el numero de espacios que ocupa el tipo de barco que corresponda.
typedef unsigned short int GameShips[ GAME_SHIPS_TYPES ][ GAME_SHIPS_PROPERTIES ];
// Definición de la estructura para el posicionamiento en el tablero del juego.
typedef struct {
    unsigned short int
        column, row;
} GameGridPosition;
// Definición de la estructura del jugador.
typedef struct {
    char name[ GAME_PLAYER_NAME_MAX_LENGHT ];
    GameGridPosition position;
    ShotTypes shotType;
    GameShips remainingShips;
    GameGrid
        grid, shotsGrid;
    int score;
    unsigned short int
        shots, hits, ships;
} GamePlayer;
// Definición de la estructura de la IA.
typedef struct {
    AIModes aiMode;
    GameGridPosition
        position, hitPosition, firstHitPosition;
    ShotTypes shotType;
    GameShips remainingShips;
    GameGrid
        grid, shotsGrid;
    AIShotDirections
        direction, hitDirection;
    unsigned short int
        shots, hits, ships;
} GameAI;
// Definición de la estructura del juego.
typedef struct {
    bool gameOver, playerShipsRandom;
    int scoreMultiplier;
    GameGrid printerGrid;
    GamePhases gamePhase;
    GameAI ai;
    GamePlayer player;
} GameStructure;
///////////////////////////////////////////
/// V A R I A B L E S   E X T E R N A S ///
///////////////////////////////////////////
// Variable global, que indica si el juego tiene o no tiene activado el modo debug, se inicializa en 'main.c'.
extern bool _Debug_Mode_;
#endif // DEFINITIONS_H
