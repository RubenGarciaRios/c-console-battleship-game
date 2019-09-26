///////////////////////
/// I N C L U D E S ///
///////////////////////
/// Librerías estandar.
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
/// Otras librerías.
#include <conio.h>
/// Cabeceras.
#include "definitions.h"
#include "printers.h"
#include "game.h"
#include "utils.h"
///////////////////////////////////////
/// I N I C I A L I Z A C I O N E S ///
///////////////////////////////////////
bool _Debug_Mode_ = false;
///////////////
/// M A I N ///
///////////////
int main( void ) {
    // Estructura del juego.
    GameStructure gameStructure;
    // Opciones de los menús.
    GameMainMenuOptions mainMenuSelectedOption;
    GameOptionsMenuOptions optionsMenuSelectectedOption;
    gameStructure.playerShipsRandom = false;
    // Bucle principal del juego.
    do {
        /* MENU PRINCIPAL */
        mainMenuSelectedOption = gameMenu(
            "HUNDIR LA FLOTA", concatenate( concatenate( "Men", charToString( LOWERCASE_U ) ), " principal." ),
            "> ", VERTICAL, 3, 1, 5, "JUEGO NUEVO", "CARGAR", "OPCIONES", "CREDITOS", "SALIR" );
        switch ( mainMenuSelectedOption ) {
            // Empieza el juego desde el principio.
            case GAME_START:
                if( !hasGameSave( ) )
                    gameController( &gameStructure, false );
                else if ( confirm( "AVISO", concatenate(
                                       concatenate( "Si empieza un juego nuevo se sobreescribir", charToString( LOWERCASE_A ) ),
                                       " la partida guardada." ) ) )
                    gameController( &gameStructure, false );
            break;
            case GAME_LOAD_GAME:
                if ( loadGame( &gameStructure ) ) {
                    gameController( &gameStructure, true );
                }
            break;
            // Accede a las opciones disponibles del juego.
            case GAME_OPTIONS:
                /* MENU DE OPCIONES */
                optionsMenuSelectectedOption = gameMenu(
                    "OPCIONES DEL JUEGO", concatenate( concatenate( "Men", charToString( LOWERCASE_U ) ), " de opciones." ),
                    "> ", HORIZONTAL, 3, 1, 2,
                    _Debug_Mode_ ? "DESACTIVAR EL MODO DEBUG" : "ACTIVAR EL MODO DEBUG",
                    gameStructure.playerShipsRandom ? "DESACTIVAR BARCOS DEL JUGADOR ALEATORIOS" : "ACTIVAR BARCOS DEL JUGADOR ALEATORIOS" );
                switch ( optionsMenuSelectectedOption ) {
                    // Activa / Desactiva el modo debug.
                    case TOGGLE_GAME_DEBUG_MODE:
                        _Debug_Mode_ = ( _Debug_Mode_ ) ? false : true;
                        clearConsole( );
                        printStringWithColor( ( _Debug_Mode_ ) ? "\n MODO DEBUG ACTIVADO." : "\n MODO DEBUG DESACTIVADO.\n", GAME_COLOR_GREEN );
                    break;
                    // Activa / Desactiva el posicionamiento aleatorio de los barcos del jugador.
                    case TOGGLE_PLAYER_SHIPS_RANDOM:
                    gameStructure.playerShipsRandom = ( gameStructure.playerShipsRandom ) ? false : true;
                    clearConsole( );
                    printStringWithColor( ( gameStructure.playerShipsRandom ) ? "\n POSICIONAMIENTO ALEATORIO DE LOS BARCOS DEL JUGADOR ACTIVADO.\n" : "\n POSICIONAMIENTO ALEATORIO DE LOS BARCOS DEL JUGADOR DESACTIVADO.", GAME_COLOR_GREEN );
                    case GAME_OPTIONS_MENU_RETURN: break;
                    default:
                        throwError( GAME_ERROR_INVALID_MENU_OPTION );
                    break;
                }
                if ( optionsMenuSelectectedOption != GAME_OPTIONS_MENU_RETURN ) {
                    printContinue( );
                }
            break;
            case GAME_CREDITS:
                printGameCredits( );
            break;
            // Sale del juego.
            case GAME_MAIN_MENU_RETURN:
            case GAME_EXIT:
                clearConsole( );
                printStringWithColor( "Saliendo...\n", GAME_COLOR_YELLOW );
            break;
            default:
                throwError( GAME_ERROR_INVALID_MENU_OPTION );
            break;
        }
    } while ( mainMenuSelectedOption != GAME_EXIT && mainMenuSelectedOption != GAME_MENU_RETURN );
    return 0;
}
