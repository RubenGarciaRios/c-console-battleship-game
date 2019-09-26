/////////////////
/// CABECERAS ///
/////////////////
#include "game.h"
/////////////////
/// FUNCIONES ///
/////////////////
void gameGridInitialization( GameGrid *gameGrid, char initialization ) {
    unsigned short int
        i = 0, j = 0;
    // Bucle de inicialización.
    for ( i = 0; i < GAME_GRID_ROWS; i++ )
        for ( j = 0; j < GAME_GRID_COLS; j++ )
            ( *gameGrid )[ i ][ j ] = initialization;
}
/////////////////////////////////////////////////////////////
void gameShipsInitialization( GameShips *gameShips ) {
    unsigned short int
        i = 0, j = 0;
    GameShips defaultshipsConfiguration = {
        { GAME_SHIP_BATTLESHIP_COUNT, GAME_SHIP_BATTLESHIP_SPACING },
        { GAME_SHIP_CRUISER_COUNT,    GAME_SHIP_CRUISER_SPACING },
        { GAME_SHIP_SUBMARINE_COUNT,  GAME_SHIP_SUBMARINE_SPACING },
        { GAME_SHIP_DESTROYER_COUNT,  GAME_SHIP_DESTROYER_SPACING } };
    // Bucle de inicialización.
    for ( i = 0; i < GAME_SHIPS_TYPES; i++ )
        for ( j = 0; j < GAME_SHIPS_PROPERTIES; j++ )
            ( *gameShips )[ i ][ j ] = defaultshipsConfiguration[ i ][ j ];
}
/////////////////////////////////////////////////////////////
void getPlayerName( char *playerName ) {
    char maxChars[ 2 ];
    short
        column, line;
    // Control del nombre del jugador.
    itoa( GAME_PLAYER_NAME_MAX_LENGHT - 1, maxChars, 10 );
    strcpy( playerName, "" );
    clearConsole( );
    printMessage( "NOMBRE DEL JUGADOR",
        concatenate( concatenate( "El nombre no debe exceder los ",  maxChars ), " caracteres." ), 0, 1 );
    printf( "\n\n => " );
    getConsoleCursorPosition( &column, &line );
    do {
        setConsoleCursorPosition( column, line );
        fgets( playerName, GAME_PLAYER_NAME_MAX_LENGHT, stdin );
        fflush( stdin );
        size_t nameLength = strlen( playerName ) - 1;
        if ( *playerName && playerName[ nameLength ] == '\n' )
            playerName[ nameLength ] = '\0';
        // Elimna los espacios no permitidos en el nombre.
        strcpy( playerName, trim( playerName ) );
    } while ( strlen( playerName ) == 0 );
}
/////////////////////////////////////////////////////////////
bool validateShipPosition( GameGrid *gameGrid, GameGridPosition *position, Orientations orientation, bool initialPosition ) {
    bool valid = true;
    // Actual.
    if ( ( *gameGrid )[ position->row ][ position->column ] != GAME_GRID_WATER )
        valid = false;
    // Superior.
    if ( position->row + 1 < GAME_GRID_ROWS && ( *gameGrid )[ position->row + 1 ][ position->column ] != GAME_GRID_WATER )
        valid = false;
    // Derecha.
    if ( position->column + 1 < GAME_GRID_COLS && ( *gameGrid )[ position->row ][ position->column + 1 ] != GAME_GRID_WATER )
        valid = false;
    // Diagonal superior izquierda.
    if ( position->column - 1 >= 0 && position->row + 1 < GAME_GRID_ROWS && ( *gameGrid )[ position->row + 1 ][ position->column - 1 ] != GAME_GRID_WATER )
        valid = false;
    // Diagonal superior derecha.
    if ( position->column + 1 < GAME_GRID_COLS && position->row + 1 < GAME_GRID_ROWS && ( *gameGrid )[ position->row + 1 ][ position->column + 1 ] != GAME_GRID_WATER )
        valid = false;
    // Diagonal inferior izquierda.
    if ( position->column - 1 >= 0 && position->row - 1 >= 0 && ( *gameGrid )[ position->row - 1 ][ position->column - 1 ] != GAME_GRID_WATER )
        valid = false;
    // Diagonal inferior derecha.
    if ( position->column + 1 < GAME_GRID_COLS && position->row - 1 >= 0 && ( *gameGrid )[ position->row - 1 ][ position->column + 1 ] != GAME_GRID_WATER )
        valid = false;
    // Siempre que la parte del barco tratada no sea la posicion inicial del barco, tendrá un tratamiento distinto.
    // - Si el posicionamiento es vertical, no se tendrá encuentra la posición inferior a la actual.
    // - Si el posicionamiento es Horizontal, no se tendrá en cuenta la posición a la izquierda a la actual.
    if ( !initialPosition )
        switch( orientation ) {
            case VERTICAL:
               // Iquierda.
               if ( position->column - 1 >= 0 && ( *gameGrid )[ position->row ][ position->column - 1 ] != GAME_GRID_WATER )
                   valid = false;
            break;
            case HORIZONTAL:
                // Inferior.
                if ( position->row - 1 >= 0 && ( *gameGrid )[ position->row - 1 ][ position->column ] != GAME_GRID_WATER )
                    valid = false;
            break;
        }
    // Si por el contrario la pieza del barco que se valida, corresponde a la inicial.
    // - Se tratan la inferior y la izquierda a la actual, y las diagonales inferiores.
    else {
        // Iquierda.
        if ( position->column - 1 >= 0 && ( *gameGrid )[ position->row ][ position->column - 1 ] != GAME_GRID_WATER )
            valid = false;
        // Inferior.
        if ( position->row - 1 >= 0 && ( *gameGrid )[ position->row - 1 ][ position->column ] != GAME_GRID_WATER )
            valid = false;
    }
    return valid;
}
/////////////////////////////////////////////////////////////
bool setPlayerShipPosition( GameGrid *playerGrid, unsigned short int shipSpacing ) {
    unsigned short int
        i = 0, j = 0;
    bool
        validPosition, wrongShipPosition, initialPosition;
    short
        column = 10, line = 1;
    GameGrid shipControl;
    Orientations orientation = VERTICAL;
    GameGridPosition
        currentPosition = { 0, 0 }, shipPiecePosition = { 0, 0 };
    char key = '\n';
    do {
        // Bucle de inicialización.
        for ( i = 0; i < GAME_GRID_ROWS; i++ )
            for ( j = 0; j < GAME_GRID_COLS; j++ )
                shipControl[ i ][ j ] = ( *playerGrid )[ i ][ j ];
        // Control del posicionamiento del barco seleccionado en el tablero del juego.
        validPosition = true;
        wrongShipPosition = false;
        switch( key ) {
            case KEYCODE_UP:
                ( currentPosition.row > 0 ) ? currentPosition.row-- : 0;
            break;
            case KEYCODE_LEFT:
                ( currentPosition.column > 0 ) ? currentPosition.column-- : 0;
            break;
            case KEYCODE_DOWN:
                ( currentPosition.row + ( ( orientation == VERTICAL ) ? shipSpacing : 0 ) < GAME_GRID_ROWS - ( orientation == HORIZONTAL ) ? 1 : 0 ) ? currentPosition.row++ : 0;
            break;
            case KEYCODE_RIGHT:
                ( currentPosition.column + ( ( orientation == HORIZONTAL ) ? shipSpacing : 0 ) < GAME_GRID_COLS - ( orientation == VERTICAL ) ? 1 : 0 ) ? currentPosition.column++ : 0;
            break;
            case KEYCODE_R:
                orientation = ( orientation == VERTICAL ) ? HORIZONTAL : VERTICAL;
                // Control del posicionamiento en la rotación.
                if ( orientation == VERTICAL )
                    currentPosition.row = ( currentPosition.row + shipSpacing ) < GAME_GRID_ROWS ? currentPosition.row : GAME_GRID_ROWS - shipSpacing;
                if ( orientation == HORIZONTAL )
                    currentPosition.column = ( currentPosition.column + shipSpacing ) < GAME_GRID_COLS ? currentPosition.column : GAME_GRID_COLS - shipSpacing;
            break;
        }
        // Posicionamiento del barco selecionado en base a la orientación.
        initialPosition = true;
        switch( orientation ) {
            case VERTICAL:
                shipPiecePosition.column = currentPosition.column;
                for ( i = currentPosition.row; i < currentPosition.row + shipSpacing; i++ ) {
                    shipPiecePosition.row = i;
                    validPosition = validateShipPosition( &shipControl, &shipPiecePosition, orientation, initialPosition );
                    if ( !validPosition )
                        wrongShipPosition = true;
                    shipControl[ i ][ currentPosition.column ] = ( validPosition == true ) ? GAME_GRID_SHIP : GAME_GRID_WRONG_POSITION;
                    initialPosition = false;
                }
            break;
            case HORIZONTAL:
                shipPiecePosition.row = currentPosition.row;
                for ( i = currentPosition.column; i < currentPosition.column + shipSpacing; i++ ) {
                    shipPiecePosition.column = i;
                    validPosition = validateShipPosition( &shipControl, &shipPiecePosition, orientation, initialPosition );
                    if ( !validPosition )
                        wrongShipPosition = true;
                    shipControl[ currentPosition.row ][ i ] = ( validPosition == true ) ? GAME_GRID_SHIP : GAME_GRID_WRONG_POSITION;
                    initialPosition = false;
                }
            break;
        }
        clearConsole( );
        printGameGrid( &shipControl, column, line );
        if ( wrongShipPosition )
            printStringWithColor( "\n\n\tNo se puede colocar el barco en la posicion que desea.", GAME_COLOR_RED );
        printf("\n\n INSTRUCCIONES:\n\n Use las teclas:\n 'ARRIBA', 'ABAJO', 'IZQUIERDA' y 'DERECHA' para mover el barco de posici%cn.\n\n Use la tecla:\n 'R' para rotar el barco.\n\n Una vez decidido el lugar, presione la tecla 'ENTER'.\n", LOWERCASE_O );
    } while ( ( key = getch( ) ) != KEYCODE_ENTER || wrongShipPosition );
    // Si el posicionamiento del barco es correcto se copia a tablero del jugador.
    for ( i = 0; i < GAME_GRID_ROWS; i++ )
        for ( j = 0; j < GAME_GRID_COLS; j++ )
            ( *playerGrid )[ i ][ j ] = shipControl[ i ][ j ];
    return true;
}
/////////////////////////////////////////////////////////////
void cloneGrid( GameGrid *destination, GameGrid *source ) {
    unsigned short int
        i = 0, j = 0;
    // Bucle de clonación.
    for ( i = 0; i < GAME_GRID_ROWS; i++ )
        for ( j = 0; j < GAME_GRID_COLS; j++ )
            (*destination)[ i ][ j ] = ( *source )[ i ][ j ];
}
/////////////////////////////////////////////////////////////
void setRandomGrid( GameGrid *randomGrid ) {
    unsigned short int
        i = 0, j = 0, prevent = 0;
    bool
        placeShip, validPosition, wrongShipPosition, initialPosition;
    unsigned short int
        remainingShips = GAME_SHIP_TOTAL_COUNT, shipSpacing = 0, shipType = 0;
    GameShips gameShips;
    GameGrid shipControl;
    Orientations orientation;
    GameGridPosition
        shipPosition = { 0, 0 }, shipPiecePosition = { 0, 0 };
    // Inicializa los barcos del jugador.
    gameShipsInitialization( &gameShips );    
    // Selección y colocación de barcos en el tablero del jugador.
    do {
        prevent = 0;
        progressBar( "Colocando los barcos de forma aleatoria", 40, GAME_SHIP_TOTAL_COUNT, GAME_SHIP_TOTAL_COUNT - remainingShips );
        // Obtención de una orientación aleatoria.
        orientation = rand( ) % 2;
        // Obtención de un tipo de barco aleatorio.
        shipType = rand( ) % ( GAME_SHIPS_TYPES );
        // Restauración del control de posicionamiento de los barcos.
        placeShip = true;
        switch( shipType ) {
            case BATTLESHIP:
                if ( gameShips[ BATTLESHIP ][ 0 ] > 0 ) {
                    shipSpacing = gameShips[ BATTLESHIP ][ 1 ];
                    gameShips[ BATTLESHIP ][ 0 ]--;
                } else placeShip = false;
            break;
            case CRUISER:
                if ( gameShips[ CRUISER ][ 0 ] > 0 ) {
                    shipSpacing = gameShips[ CRUISER ][ 1 ];
                    gameShips[ CRUISER ][ 0 ]--;
                } else placeShip = false;
            break;
            case SUBMARINE:
                if ( gameShips[ SUBMARINE ][ 0 ] > 0 ) {
                    shipSpacing = gameShips[ SUBMARINE ][ 1 ];
                    gameShips[ SUBMARINE ][ 0 ]--;
                } else placeShip = false;
            break;
            case DESTROYER:
                if ( gameShips[ DESTROYER ][ 0 ] > 0 ) {
                    shipSpacing = gameShips[ DESTROYER ][ 1 ];
                    gameShips[ DESTROYER ][ 0 ]--;
                } else placeShip = false;
            break;
            default: throwError( GAME_ERROR_INVALID_SHIP ); break;
        }
        // En caso de que se haya elegido correctamente el tipo de barco se procede a su posicionamiento.
        if( placeShip ) {
            do {
                // Clona el tablero de la IA para hacer un control de las posiciones de los barcos en base a su estado actual.
                for ( i = 0; i < GAME_GRID_ROWS; i++ )
                    for ( j = 0; j < GAME_GRID_COLS; j++ )
                        shipControl[ i ][ j ] = ( *randomGrid )[ i ][ j ];
                // Control de la posición, la posición más la longitud del barco no puede exceder el tamaño de las columnas ni las filas del tablero.
                shipPosition.row = rand( ) % ( GAME_GRID_ROWS - ( ( orientation == VERTICAL ) ? shipSpacing : 0 ) );
                shipPosition.column = rand( ) % ( GAME_GRID_COLS - ( ( orientation == HORIZONTAL ) ? shipSpacing : 0 ) );
                /* MENOS EFICIENTE.
                do {
                    shipPosition.row = rand( ) % GAME_GRID_ROWS;
                    shipPosition.column = rand( ) % GAME_GRID_COLS;
                } while(
                    ( orientation == VERTICAL && shipPosition.row + shipSpacing >= GAME_GRID_ROWS ) ||
                    ( orientation == HORIZONTAL && shipPosition.column + shipSpacing >= GAME_GRID_COLS )
                );
                */
                initialPosition = true;
                wrongShipPosition = false;
                // Colocación en base a la orientación del barco.
                switch( orientation ) {
                    case VERTICAL:
                        shipPiecePosition.column = shipPosition.column;
                        for ( i = shipPosition.row; i < shipPosition.row + shipSpacing; i++ ) {
                            shipPiecePosition.row = i;
                            validPosition = validateShipPosition( &shipControl, &shipPiecePosition, orientation, initialPosition );
                            if ( !validPosition ) {
                                wrongShipPosition = true;
                                break;
                            } else
                                shipControl[ i ][ shipPosition.column ] = ( validPosition == true ) ? GAME_GRID_SHIP : GAME_GRID_WRONG_POSITION;
                            initialPosition = false;
                        }
                    break;
                    case HORIZONTAL:
                        shipPiecePosition.row = shipPosition.row;
                        for ( i = shipPosition.column; i < shipPosition.column + shipSpacing; i++ ) {
                            shipPiecePosition.column = i;
                            validPosition = validateShipPosition( &shipControl, &shipPiecePosition, orientation, initialPosition );
                            if ( !validPosition ) {
                                wrongShipPosition = true;
                                break;
                            } else
                                shipControl[ shipPosition.row ][ i ] = ( validPosition == true ) ? GAME_GRID_SHIP : GAME_GRID_WRONG_POSITION;
                            initialPosition = false;
                        }
                    break;
                }
                // Utilizado en caso de dead loop.
                prevent++;
                if ( prevent > 300 ) {
                    gameGridInitialization( *&randomGrid, GAME_GRID_WATER );
                    setRandomGrid( *&randomGrid );
                    return;
                }
            // Repìte el proceso mientras la posición del barco sea incorrecta.
            } while ( wrongShipPosition );
            // Si el posicionamiento del barco es correcto se copia a tablero de la IA.
            for ( i = 0; i < GAME_GRID_ROWS; i++ )
                for ( j = 0; j < GAME_GRID_COLS; j++ )
                    ( *randomGrid )[ i ][ j ] = shipControl[ i ][ j ];
            remainingShips--;
        }
    } while( remainingShips != 0 );
    progressBar( "Colocando los barcos de la IA", 40, GAME_SHIP_TOTAL_COUNT, GAME_SHIP_TOTAL_COUNT - remainingShips );
}
/////////////////////////////////////////////////////////////
bool setPlayerGrid( GameGrid *playerGrid ) {
    bool placeShip, skip;
    unsigned short int
        remainingShips = GAME_SHIP_TOTAL_COUNT, shipSpacing = 0;
    GameShips gameShips;
    char *shipNames[ GAME_SHIPS_TYPES ] = {
        "ACORAZADO",
        "CRUCERO",
        "SUBMARINO",
        "DESTRUCTOR"
    };
    // Inicializa los barcos del jugador.
    gameShipsInitialization( &gameShips );
    // Selección y colocación de barcos en el tablero del jugador.
    do {
        skip = false;
        placeShip = true;
        switch( gameMenu(
            concatenate( concatenate( "SELECCI", charToString( UPPERCASE_O ) ), "N DE BARCOS" ),
            "Seleccione uno de los barcos", "> ", HORIZONTAL, 3, 1, 4,
            /* OPCIONES DEL MENÚ CON LOS NOMBRES DE LOS BARCOS, SEGUIDO DE SU CANTIDAD RESTANTE. */
            concatenate( concatenate( shipNames[ BATTLESHIP ], " x" ),  charToString( ( char ) gameShips[ BATTLESHIP ][ 0 ] + '0' ) ),
            concatenate( concatenate( shipNames[ CRUISER ], " x" ),     charToString( ( char ) gameShips[ CRUISER ][ 0 ]    + '0' ) ),
            concatenate( concatenate( shipNames[ SUBMARINE ], " x" ),   charToString( ( char ) gameShips[ SUBMARINE ][ 0 ]  + '0' ) ),
            concatenate( concatenate( shipNames[ DESTROYER ], " x" ),   charToString( ( char ) gameShips[ DESTROYER ][ 0 ]  + '0' ) ) ) - 1 ) {
            case BATTLESHIP:
                if ( gameShips[ BATTLESHIP ][ 0 ] > 0 ) {
                    shipSpacing = gameShips[ BATTLESHIP ][ 1 ];
                    gameShips[ BATTLESHIP ][ 0 ]--;
                } else placeShip = false;
            break;
            case CRUISER:
                if ( gameShips[ CRUISER ][ 0 ] > 0 ) {
                    shipSpacing = gameShips[ CRUISER ][ 1 ];
                    gameShips[ CRUISER ][ 0 ]--;
                } else placeShip = false;
            break;
            case SUBMARINE:
                if ( gameShips[ SUBMARINE ][ 0 ] > 0 ) {
                    shipSpacing = gameShips[ SUBMARINE ][ 1 ];
                    gameShips[ SUBMARINE ][ 0 ]--;
                } else placeShip = false;
            break;
            case DESTROYER:
                if ( gameShips[ DESTROYER ][ 0 ] > 0 ) {
                    shipSpacing = gameShips[ DESTROYER ][ 1 ];
                    gameShips[ DESTROYER ][ 0 ]--;
                } else placeShip = false;
            break;
            case GAME_MENU_RETURN - 1:
                if ( confirm( "AVISO", "Si sale se eliminan todas las posiciones de los barcos." ) )
                    return false;
                else skip = true;
            break;
            default: throwError( GAME_ERROR_INVALID_SHIP ); break;
        }
        // Si quedan barcos disponibles del tipo seleccionado, se procede a su posicionamiento.
        if ( placeShip && !skip ) {
            setPlayerShipPosition( *&playerGrid, shipSpacing );
            remainingShips--;
        // En caso contrario se imprime un error informativo.
        } else if( !skip ) {
            printStringWithColor( concatenate(
                concatenate( "\n No quedan m", charToString( LOWERCASE_A ) ), "s barcos de este tipo." ),
                GAME_COLOR_RED );
            printContinue( );
        }
    } while( remainingShips != 0 );
    return true;
}
/////////////////////////////////////////////////////////////
bool getPlayerShoot( GameGridPosition *position, bool *exit ) {
    unsigned short int
        i = 0;
    char shoot[ 3 ];
    bool validRow = false, validColumn = false;
    position->row = 0;
    position->column = 0;
    printf( "\n Introduzca la fila y la columna. Ejemplo 'a0', o 'x' para salir: " );
    fgets ( shoot, sizeof shoot, stdin );
    fflush( stdin );
    size_t shootLength = strlen( shoot ) - 1;
    if ( *shoot && shoot[ shootLength ] == '\n' )
        shoot[ shootLength ] = '\0';
    // En caso de que se introduzca la palabra exit se notificará a game controller.
    if ( toupper( shoot[ 0 ] ) == 'X' ) {
        *exit = true;
        return false;
    }
    // Validación de las filas.
    for ( i = 0; i < GAME_GRID_ROWS; i++ ) {
        if ( toupper( shoot[ 0 ] ) == GAME_GRID_ROWS_ENUMERATION[ i ] ) {
            validRow = true;
            break;
        }
        position->row++;
    }
    // Validación de las columnas.
    for ( i = 0; i < GAME_GRID_COLS; i++ ) {
        if ( toupper( shoot[ 1 ] ) == GAME_GRID_COLS_ENUMERATION[ i ] ) {
            validColumn = true;
            break;
        }
        position->column++;
    }
    return validRow && validColumn;
}
/////////////////////////////////////////////////////////////
ShotTypes shootController( GameGrid *gameGrid, GameGrid *gameGridShots, GameGridPosition *position, unsigned short int *shipSize ) {
    char cellType = ( *gameGrid )[ position->row ][ position->column ];
    ShotTypes shotType;
    bool
        top = true, left = true, bottom = true, right = true;
    unsigned short int
        initialRow = position->row, initialColumn = position->column, n = 0;
    *shipSize = 0;
    // Valida si la posición, es una posición repetida.
    if ( ( *gameGridShots )[ position->row ][ position->column ] != GAME_GRID_NULL )
        return SHOT_INVALID;
    // Agua.
    if( cellType == GAME_GRID_WATER )
        shotType = SHOT_MISS;
    // Inteligencia de colisiones.
    else {
        shotType = SHOT_HIT;
        n++;
        // Colisiones hacia arriba.
        if ( position->row < GAME_GRID_ROWS - 1 ) do {
                if ( position->row == GAME_GRID_ROWS - 1 ) break;
                position->row++;
                if ( ( *gameGridShots )[ position->row ][ position->column ] != GAME_GRID_DAMAGED
                && ( *gameGrid )[ position->row ][ position->column ] == GAME_GRID_SHIP ) {
                    top = false;
                    break;
                }
                if ( ( *gameGridShots )[ position->row ][ position->column ] == GAME_GRID_DAMAGED ) n++;
            } while ( ( *gameGrid )[ position->row ][ position->column ] != GAME_GRID_WATER );
        else top = true;
        position->row = initialRow;
        // Colisiones hacia la izquierda.
        if ( position->column > 0 ) do {
                if( position->column == 0 ) break;
                position->column--;
                if ( ( *gameGridShots )[ position->row ][ position->column ] != GAME_GRID_DAMAGED
                && ( *gameGrid )[ position->row ][ position->column ] == GAME_GRID_SHIP ) {
                    left = false;
                    break;
                }
                if ( ( *gameGridShots )[ position->row ][ position->column ] == GAME_GRID_DAMAGED ) n++;
            } while ( ( *gameGrid )[ position->row ][ position->column ] != GAME_GRID_WATER );
        else left = true;
        position->column = initialColumn;
        // Colisiones hacia abajo.
        if ( position->row > 0 ) do {
                if ( position->row == 0 ) break;
                position->row--;
                if ( ( *gameGridShots )[ position->row ][ position->column ] != GAME_GRID_DAMAGED
                && ( *gameGrid )[ position->row ][ position->column ] == GAME_GRID_SHIP ) {
                    bottom = false;
                    break;
                }
                if ( ( *gameGridShots )[ position->row ][ position->column ] == GAME_GRID_DAMAGED ) n++;
            } while ( ( *gameGrid )[ position->row ][ position->column ] != GAME_GRID_WATER );
        else bottom = true;
        position->row = initialRow;
        // Colisiones hacia la derecha.
        if ( position->column < GAME_GRID_COLS - 1 ) do {
                if ( position->column == GAME_GRID_COLS - 1 ) break;
                position->column++;
                if ( ( *gameGridShots )[ position->row ][ position->column ] != GAME_GRID_DAMAGED
                && ( *gameGrid )[ position->row ][ position->column ] == GAME_GRID_SHIP ) {
                    right = false;
                    break;
                }
                if ( ( *gameGridShots )[ position->row ][ position->column ] == GAME_GRID_DAMAGED ) n++;
            } while ( ( *gameGrid )[ position->row ][ position->column ] != GAME_GRID_WATER );
        else right = true;
        position->column = initialColumn;
        // En caso de que se haya hundido el barco, se devuelve su longitud.
        if( top && left && bottom && right ) {
            shotType = SHOT_SUNKEN;
            *shipSize = n;
        }
    }
    // Se guarda el resultado en el tablero de disparos.
    ( *gameGridShots )[ position->row ][ position->column ] = shotType == SHOT_MISS ? GAME_GRID_WATER : GAME_GRID_DAMAGED;
    // En caso de haber hundido el barco, se reemplazan todas las posiciones de tocado por hundido.
    if ( shotType == SHOT_SUNKEN )
        updateDamaGedShipToShunken( gameGridShots, position );
    return shotType;
}
/////////////////////////////////////////////////////////////
void updateDamaGedShipToShunken( GameGrid *gameGridShots, GameGridPosition *position ) {
    int row, column;
    row = position->row + 1;
    column = position->column;
    // Cambia al estado hundido la posición que ha indicado el estado hundido.
    ( *gameGridShots )[ position->row ][ position->column ] = GAME_GRID_SHUNKEN;
    // Busca la orientación del barco y cambia el estado dañado por hundido
    // Arriba.
    while ( row <= GAME_GRID_ROWS - 1 ) {
        if ( ( *gameGridShots )[ row ][ column ] != GAME_GRID_DAMAGED ) break;
        else ( *gameGridShots )[ row ][ column ] = GAME_GRID_SHUNKEN;
        row++;
    }
    row = position->row;
    column = position->column - 1;
    // Izquierda.
    while ( column >= 0 ) {
        if ( ( *gameGridShots )[ row ][ column ] != GAME_GRID_DAMAGED ) break;
        else ( *gameGridShots )[ row ][ column ] = GAME_GRID_SHUNKEN;
        column--;
    }
    row = position->row  - 1;
    column = position->column;
    // Abajo.
    while ( row >= 0 ) {
        if ( ( *gameGridShots )[ row ][ column ] != GAME_GRID_DAMAGED ) break;
        else ( *gameGridShots )[ row ][ column ] = GAME_GRID_SHUNKEN;
        row--;
    }
    row = position->row;
    column = position->column + 1;
    // Derecha.
    while ( column <= GAME_GRID_COLS - 1 ) {
        if ( ( *gameGridShots )[ row ][ column ] != GAME_GRID_DAMAGED ) break;
        else ( *gameGridShots )[ row ][ column ] = GAME_GRID_SHUNKEN;
        column++;
    }
}
/////////////////////////////////////////////////////////////
void updateRemainingShips( GameShips *remainingShips, unsigned short int shipSize ) {
    unsigned short int i;
    // Bucle de búsqueda.
    for ( i = 0; i < GAME_SHIPS_TYPES; i++ )
        if( ( *remainingShips )[ i ][ 1 ] == shipSize ) {
            // En caso de encontrarlo lo decrementa, si procede.
            if ( ( *remainingShips )[ i ][ 0 ] > 0 ) {
                ( *remainingShips )[ i ][ 0 ]--;
                return;
            }
        }
}
/////////////////////////////////////////////////////////////
bool validateAIRandomPosition( GameGrid *gameGrid, GameGridPosition *position, GameShips *remainingShips ) {
    unsigned short int
        i, remainingShipsMinSize = 0;
    int
        verticalSpacing = 0, horizontalSpacing = 0, row, column;
    // Obtiene el tamaño del barco más pequeño, de entre los barcos que le quedan por hundir a la IA.
    for ( i = 0; i < GAME_SHIPS_TYPES; i++ )
        if( ( *remainingShips )[ i ][ 1 ] < remainingShipsMinSize || remainingShipsMinSize == 0 )
            remainingShipsMinSize = ( *remainingShips )[ i ][ 1 ];
    row = position->row;
    column = position->column;
    // En la posición actual se incrementa el espacio en 1 siempre y cuando no se haya resuelto dicha posición.
    if ( ( *gameGrid )[ row ][ column ] == GAME_GRID_NULL ) {
        verticalSpacing++;
        horizontalSpacing++;
    } else return false;
    row = position->row + 1;
    column = position->column;
    // Arriba.
    while ( row <= GAME_GRID_ROWS - 1 ) {
        if ( ( *gameGrid )[ row ][ column ] != GAME_GRID_NULL ) break;
        else verticalSpacing++;
        row++;
    }
    row = position->row;
    column = position->column - 1;
    // Izquierda.
    while ( column >= 0 ) {
        if ( ( *gameGrid )[ row ][ column ] != GAME_GRID_NULL ) break;
        else horizontalSpacing++;
        column--;
    }
    row = position->row - 1;
    column = position->column;
    // Abajo.
    while ( row >= 0 ) {
        if ( ( *gameGrid )[ row ][ column ] != GAME_GRID_NULL ) break;
        else verticalSpacing++;
        row--;
    }
    row = position->row;
    column = position->column + 1;
    // Derecha.
    while ( column <= GAME_GRID_COLS - 1 ) {
        if ( ( *gameGrid )[ row ][ column ] != GAME_GRID_NULL ) break;
        else horizontalSpacing++;
        column++;
    }
    // SOLO EN CASO DE MODO DEBUG.
    if ( _Debug_Mode_ ) {
        printf( "\n validateAIRandomPosition::position[ %c%c ], remainingShipsMinSize = %d",
                GAME_GRID_ROWS_ENUMERATION[ position->row ], GAME_GRID_COLS_ENUMERATION[ position->column ], remainingShipsMinSize );
        printf( "\n validateIARandomPosition::verticalSpacing %d, horizontalSpacing %d, valid %d",
                verticalSpacing, horizontalSpacing, ( remainingShipsMinSize <= verticalSpacing || remainingShipsMinSize <= horizontalSpacing ) );
        printContinue( );
    }
    return ( remainingShipsMinSize <= verticalSpacing || remainingShipsMinSize <= horizontalSpacing );
}
/////////////////////////////////////////////////////////////
bool validateAIRandomDirection( GameGrid *gameGrid, GameGridPosition *position, GameShips *remainingShips, AIShotDirections direction ) {
    unsigned short int
        i, remainingShipsMinSize = 0;
    int
        topSpacing = 0, leftSpacing = 0, bottomSpacing = 0, rightSpacing = 0, row, column;
    // Obtiene el tamaño del barco más pequeño, de entre los barcos que le quedan por hundir a la IA.
    for ( i = 0; i < GAME_SHIPS_TYPES; i++ )
        if( ( *remainingShips )[ i ][ 1 ] < remainingShipsMinSize || remainingShipsMinSize == 0 )
            remainingShipsMinSize = ( *remainingShips )[ i ][ 1 ];
    // Validación en base a la dirección.
    switch( direction ) {
        case DIRECTION_TOP:
            // Arriba.
            row = position->row + 1;
            column = position->column;
            while ( row <= GAME_GRID_ROWS - 1 ) {
                if ( ( *gameGrid )[ row ][ column ] == GAME_GRID_WATER ) break;
                else topSpacing++;
                row++;
            }
            // SOLO EN CASO DE MODO DEBUG.
            if ( _Debug_Mode_ ) {
                printf( "\n validateAIRandomDirection::position[ %c%c ], remainingShipsMinSize = %d",
                        GAME_GRID_ROWS_ENUMERATION[ position->row ], GAME_GRID_COLS_ENUMERATION[ position->column ], remainingShipsMinSize );
                printf( "\n validateAIRandomDirection::topSpacing %d, valid %d", topSpacing, ( remainingShipsMinSize <= topSpacing ) );
                printContinue( );
            }
            return ( remainingShipsMinSize <= topSpacing );
        break;
        case DIRECTION_BOTTOM:
            // Abajo.
            row = position->row - 1;
            column = position->column;
            while ( row >= 0 ) {
                if ( ( *gameGrid )[ row ][ column ] == GAME_GRID_WATER ) break;
                else bottomSpacing++;
                row--;
            }
            // SOLO EN CASO DE MODO DEBUG.
            if ( _Debug_Mode_ ) {
                printf( "\n validateAIRandomDirection::position[ %c%c ], remainingShipsMinSize = %d",
                        GAME_GRID_ROWS_ENUMERATION[ position->row ], GAME_GRID_COLS_ENUMERATION[ position->column ], remainingShipsMinSize );
                printf( "\n validateAIRandomDirection::bottomSpacing %d, valid %d", bottomSpacing, ( remainingShipsMinSize <= bottomSpacing ) );
                printContinue( );
            }
            return ( remainingShipsMinSize <= bottomSpacing );
        break;
        case DIRECTION_LEFT:
            row = position->row;
            column = position->column - 1;
            // Izquierda.
            while ( column >= 0 ) {
                if ( ( *gameGrid )[ row ][ column ] == GAME_GRID_WATER ) break;
                else leftSpacing++;
                column--;
            }
            // SOLO EN CASO DE MODO DEBUG.
            if ( _Debug_Mode_ ) {
                printf( "\n validateAIRandomDirection::position[ %c%c ], remainingShipsMinSize = %d",
                        GAME_GRID_ROWS_ENUMERATION[ position->row ], GAME_GRID_COLS_ENUMERATION[ position->column ], remainingShipsMinSize );
                printf( "\n validateAIRandomDirection::leftSpacing %d, valid %d", leftSpacing, ( remainingShipsMinSize <= leftSpacing ) );
                printContinue( );
            }
            return ( remainingShipsMinSize <= leftSpacing );
        break;
        case DIRECTION_RIGHT:
            row = position->row;
            column = position->column + 1;
            // Derecha.
            while ( column <= GAME_GRID_COLS - 1 ) {
                if ( ( *gameGrid )[ row ][ column ] == GAME_GRID_WATER ) break;
                else rightSpacing++;
                column++;
            }
            // SOLO EN CASO DE MODO DEBUG.
            if ( _Debug_Mode_ ) {
                printf( "\n validateAIRandomDirection::position[ %c%c ], remainingShipsMinSize = %d",
                        GAME_GRID_ROWS_ENUMERATION[ position->row ], GAME_GRID_COLS_ENUMERATION[ position->column ], remainingShipsMinSize );
                printf( "\n validateAIRandomDirection::rightSpacing %d, valid %d", rightSpacing, ( remainingShipsMinSize <= rightSpacing ) );
                printContinue( );
            }
             return ( remainingShipsMinSize <= rightSpacing );
        break;
        default: break;
    }
    return true;
}
/////////////////////////////////////////////////////////////
void aiWaterFill( GameGrid *shotsGrid, GameGridPosition *firstPosition, GameGridPosition *hitPosition, AIShotDirections direction, bool shunken ) {
    unsigned short int i;
    // Rellena de agua las posiciones adyacentes a partir de la dirección.
    consoleLog( "\n aiWaterFill::FILL START" );
    switch ( direction ) {
        case DIRECTION_TOP:
            consoleLog( "\n aiWaterFill::direction = DIRECTION_TOP, FILL [ DIRECTION_LEFT, DIRECTION_RIGHT ]" );
            for ( i = firstPosition->row; i <= hitPosition->row; i++ ) {
                if ( _Debug_Mode_ ) printf( "\n aiController::hitPosition[ %c%c ]",
                                            GAME_GRID_ROWS_ENUMERATION[ i ], GAME_GRID_COLS_ENUMERATION[ hitPosition->column ] );
                consoleLog( "" );
                // Rellena de agua hacia la izquierda.
                if ( hitPosition->column > 0 && ( *shotsGrid )[ i ][ hitPosition->column - 1 ] == GAME_GRID_NULL )
                    ( *shotsGrid )[ i ][ hitPosition->column - 1 ] = GAME_GRID_WATER;
                // Rellena de agua hacia la derecha.
                if ( hitPosition->column < GAME_GRID_COLS - 1 && ( *shotsGrid )[ i ][ hitPosition->column + 1 ] == GAME_GRID_NULL )
                    ( *shotsGrid )[ i ][ hitPosition->column + 1 ] = GAME_GRID_WATER;
                // Solo en caso de que se haya hundido el barco.
                if ( shunken ) {
                    // Arriba.
                    if ( i < GAME_GRID_ROWS - 1 && ( *shotsGrid )[ i + 1 ][ hitPosition->column ] == GAME_GRID_NULL )
                       ( *shotsGrid )[ i + 1 ][ hitPosition->column ] = GAME_GRID_WATER;
                    // Abajo.
                    if ( i > 0 && ( *shotsGrid )[ i - 1 ][ hitPosition->column ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ i - 1 ][ hitPosition->column ] = GAME_GRID_WATER;
                    // Diagonal superior iquierda.
                    if ( i < GAME_GRID_ROWS - 1 && hitPosition->column > 0
                    && ( *shotsGrid )[ i + 1 ][ hitPosition->column - 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ i + 1 ][ hitPosition->column - 1 ] = GAME_GRID_WATER;
                    // Diagonal superior derecha.
                    if ( i < GAME_GRID_ROWS - 1 && hitPosition->column < GAME_GRID_COLS - 1
                    && ( *shotsGrid )[ i + 1 ][ hitPosition->column + 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ i + 1 ][ hitPosition->column + 1 ] = GAME_GRID_WATER;
                    // Diagonal inferior iquierda.
                    if ( i > 0 && hitPosition->column > 0
                    && ( *shotsGrid )[ i - 1 ][ hitPosition->column - 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ i - 1 ][ hitPosition->column - 1 ] = GAME_GRID_WATER;
                    // Diagonal inferior derecha.
                    if ( i > 0 && hitPosition->column < GAME_GRID_COLS - 1
                    && ( *shotsGrid )[ i - 1 ][ hitPosition->column + 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ i - 1 ][ hitPosition->column + 1 ] = GAME_GRID_WATER;
                }
            }
        break;
        case DIRECTION_LEFT:
            consoleLog( "\n aiWaterFill::direction = DIRECTION_LEFT, FILL [ DIRECTION_TOP, DIRECTION_BOTTOM ]" );
             for ( i = hitPosition->column; i <= firstPosition->column; i++ ) {
                 if ( _Debug_Mode_ ) printf( "\n aiController::hitPosition[ %c%c ]",
                                             GAME_GRID_ROWS_ENUMERATION[ hitPosition->row ], GAME_GRID_COLS_ENUMERATION[ i ] );
                 consoleLog( "" );
                // Rellena de agua hacia la arriba.
                if ( hitPosition->row < GAME_GRID_ROWS - 1 && ( *shotsGrid )[ hitPosition->row + 1 ][ i ] == GAME_GRID_NULL )
                    ( *shotsGrid )[ hitPosition->row + 1 ][ i ] = GAME_GRID_WATER;
                // Rellena de agua hacia abajo.
                if ( hitPosition->column > 0 && ( *shotsGrid )[ hitPosition->row - 1 ][ i ] == GAME_GRID_NULL )
                    ( *shotsGrid )[ hitPosition->row - 1 ][ i ] = GAME_GRID_WATER;
                // Solo en caso de que se haya hundido el barco.
                if ( shunken ) {
                    // Izquierda.
                    if ( i > 0 && ( *shotsGrid )[ hitPosition->row ][ i - 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row ][ i - 1 ] = GAME_GRID_WATER;
                    // Derecha.
                    if ( i < GAME_GRID_COLS - 1 && ( *shotsGrid )[ hitPosition->row ][ i + 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row ][ i + 1 ] = GAME_GRID_WATER;
                    // Diagonal superior iquierda.
                    if ( hitPosition->row < GAME_GRID_ROWS - 1 && i > 0
                    && ( *shotsGrid )[ hitPosition->row + 1 ][ i - 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row + 1 ][ i - 1 ] = GAME_GRID_WATER;
                    // Diagonal superior derecha.
                    if ( hitPosition->row < GAME_GRID_ROWS - 1 && i < GAME_GRID_COLS - 1
                    && ( *shotsGrid )[ hitPosition->row + 1 ][ i + 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row + 1 ][ i + 1 ] = GAME_GRID_WATER;
                    // Diagonal inferior iquierda.
                    if ( hitPosition->row > 0 && i > 0
                    && ( *shotsGrid )[ hitPosition->row - 1 ][ i - 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row - 1 ][ i - 1 ] = GAME_GRID_WATER;
                    // Diagonal inferior derecha.
                    if ( hitPosition->row > 0 && i < GAME_GRID_COLS - 1
                    && ( *shotsGrid )[ hitPosition->row - 1 ][ i + 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row - 1 ][ i + 1 ] = GAME_GRID_WATER;
                }
            }
        break;
        case DIRECTION_BOTTOM:
            consoleLog( "\n aiWaterFill::direction = DIRECTION_BOTTOM, FILL [ DIRECTION_LEFT, DIRECTION_RIGHT ]" );
             for ( i = hitPosition->row; i <= firstPosition->row; i++ ) {
                 if ( _Debug_Mode_ ) printf( "\n aiController::hitPosition[ %c%c ]",
                                             GAME_GRID_ROWS_ENUMERATION[ i ], GAME_GRID_COLS_ENUMERATION[ hitPosition->column ] );
                 consoleLog( "" );
                // Rellena de agua hacia la izquierda.
                if ( hitPosition->column > 0 && ( *shotsGrid )[ i ][ hitPosition->column - 1 ] == GAME_GRID_NULL )
                     ( *shotsGrid )[ i ][ hitPosition->column - 1 ] = GAME_GRID_WATER;
                // Rellena de agua hacia la derecha.
                if ( hitPosition->column < GAME_GRID_COLS - 1 && ( *shotsGrid )[ i ][ hitPosition->column + 1 ] == GAME_GRID_NULL )
                    ( *shotsGrid )[ i ][ hitPosition->column + 1 ] = GAME_GRID_WATER;
                // Solo en caso de que se haya hundido el barco.
                if ( shunken ) {
                    // Arriba.
                    if ( i < GAME_GRID_ROWS - 1 && ( *shotsGrid )[ i + 1 ][ hitPosition->column ] == GAME_GRID_NULL )
                       ( *shotsGrid )[ i + 1 ][ hitPosition->column ] = GAME_GRID_WATER;
                    // Abajo.
                    if ( i > 0 && ( *shotsGrid )[ i - 1 ][ hitPosition->column ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ i - 1 ][ hitPosition->column ] = GAME_GRID_WATER;
                    // Diagonal superior iquierda.
                    if ( i < GAME_GRID_ROWS - 1 && hitPosition->column > 0
                    && ( *shotsGrid )[ i + 1 ][ hitPosition->column - 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ i + 1 ][ hitPosition->column - 1 ] = GAME_GRID_WATER;
                    // Diagonal superior derecha.
                    if ( i < GAME_GRID_ROWS - 1 && hitPosition->column < GAME_GRID_COLS - 1
                    && ( *shotsGrid )[ i + 1 ][ hitPosition->column + 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ i + 1 ][ hitPosition->column + 1 ] = GAME_GRID_WATER;
                    // Diagonal inferior iquierda.
                    if ( i > 0 && hitPosition->column > 0
                    && ( *shotsGrid )[ i - 1 ][ hitPosition->column - 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ i - 1 ][ hitPosition->column - 1 ] = GAME_GRID_WATER;
                    // Diagonal inferior derecha.
                    if ( i > 0 && hitPosition->column < GAME_GRID_COLS - 1
                    && ( *shotsGrid )[ i - 1 ][ hitPosition->column + 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ i - 1 ][ hitPosition->column + 1 ] = GAME_GRID_WATER;
                }
            }
        break;
        case DIRECTION_RIGHT:
            consoleLog( "\n aiWaterFill::direction = DIRECTION_RIGHT, FILL [ DIRECTION_TOP, DIRECTION_BOTTOM ]" );
            // Dependiendo de la dirección el bucle será incremental, o decremental.
            for ( i = firstPosition->column; i <= hitPosition->column; i++ ) {
                if ( _Debug_Mode_ ) printf( "\n aiController::hitPosition[ %c%c ]",
                                            GAME_GRID_ROWS_ENUMERATION[ hitPosition->row ], GAME_GRID_COLS_ENUMERATION[ i ] );
                consoleLog( "" );
                // Rellena de agua hacia la arriba.
                if ( hitPosition->row < GAME_GRID_ROWS - 1 && ( *shotsGrid )[ hitPosition->row + 1 ][ i ] == GAME_GRID_NULL )
                    ( *shotsGrid )[ hitPosition->row + 1 ][ i ] = GAME_GRID_WATER;
                // Rellena de agua hacia abajo.
                if ( hitPosition->column > 0 && ( *shotsGrid )[ hitPosition->row - 1 ][ i ] == GAME_GRID_NULL )
                    ( *shotsGrid )[ hitPosition->row - 1 ][ i ] = GAME_GRID_WATER;
                // Solo en caso de que se haya hundido el barco.
                if ( shunken ) {
                    // Izquierda.
                    if ( i > 0 && ( *shotsGrid )[ hitPosition->row ][ i - 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row ][ i - 1 ] = GAME_GRID_WATER;
                    // Derecha.
                    if ( i < GAME_GRID_COLS - 1 && ( *shotsGrid )[ hitPosition->row ][ i + 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row ][ i + 1 ] = GAME_GRID_WATER;
                    // Diagonal superior iquierda.
                    if ( hitPosition->row < GAME_GRID_ROWS - 1 && i > 0
                    && ( *shotsGrid )[ hitPosition->row + 1 ][ i - 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row + 1 ][ i - 1 ] = GAME_GRID_WATER;
                    // Diagonal superior derecha.
                    if ( hitPosition->row < GAME_GRID_ROWS - 1 && i < GAME_GRID_COLS - 1
                    && ( *shotsGrid )[ hitPosition->row + 1 ][ i + 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row + 1 ][ i + 1 ] = GAME_GRID_WATER;
                    // Diagonal inferior iquierda.
                    if ( hitPosition->row > 0 && i > 0
                    && ( *shotsGrid )[ hitPosition->row - 1 ][ i - 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row - 1 ][ i - 1 ] = GAME_GRID_WATER;
                    // Diagonal inferior derecha.
                    if ( hitPosition->row > 0 && i < GAME_GRID_COLS - 1
                    && ( *shotsGrid )[ hitPosition->row - 1 ][ i + 1 ] == GAME_GRID_NULL )
                        ( *shotsGrid )[ hitPosition->row - 1 ][ i + 1 ] = GAME_GRID_WATER;
                }
            }
        break;
        // Este caso sólo ocurre para los barcos de longitud 1.
        case DIRECTION_NULL:
            consoleLog( "\n aiWaterFill::direction = DIRECTION_NULL, FILL [ DIRECTION_TOP, DIRECTION_LEFT, DIRECTION_BOTTOM, DIRECTION_RIGHT ]" );
             // Rellena de agua hacia la arriba.
            if ( hitPosition->row < GAME_GRID_ROWS - 1 && ( *shotsGrid )[ hitPosition->row + 1 ][ hitPosition->column ] == GAME_GRID_NULL )
                ( *shotsGrid )[ hitPosition->row + 1 ][ hitPosition->column ] = GAME_GRID_WATER;
            // Rellena de agua hacia la izquierda.
            if ( hitPosition->column > 0 && ( *shotsGrid )[ hitPosition->column ][ hitPosition->column - 1 ] == GAME_GRID_NULL )
                ( *shotsGrid )[ hitPosition->row ][ hitPosition->column - 1 ] = GAME_GRID_WATER;
            // Rellena de agua hacia abajo.
            if ( hitPosition->column > 0 && ( *shotsGrid )[ hitPosition->row - 1 ][ hitPosition->column ] == GAME_GRID_NULL )
                ( *shotsGrid )[ hitPosition->row - 1 ][ hitPosition->column ] = GAME_GRID_WATER;
            // Rellena de agua hacia la derecha.
            if ( hitPosition->column < GAME_GRID_COLS - 1 && ( *shotsGrid )[ hitPosition->column ][ hitPosition->column + 1 ] == GAME_GRID_NULL )
                ( *shotsGrid )[ hitPosition->row ][ hitPosition->column + 1 ] = GAME_GRID_WATER;
            // Diagonal superior iquierda.
            if ( hitPosition->row < GAME_GRID_ROWS - 1 && hitPosition->column > 0
            && ( *shotsGrid )[ hitPosition->row + 1 ][ hitPosition->column - 1 ] == GAME_GRID_NULL )
                ( *shotsGrid )[ hitPosition->row + 1 ][ hitPosition->column - 1 ] = GAME_GRID_WATER;
            // Diagonal superior derecha.
            if ( hitPosition->row < GAME_GRID_ROWS - 1 && hitPosition->column < GAME_GRID_COLS - 1
            && ( *shotsGrid )[ hitPosition->row + 1 ][ hitPosition->column + 1 ] == GAME_GRID_NULL )
                ( *shotsGrid )[ hitPosition->row + 1 ][ hitPosition->column + 1 ] = GAME_GRID_WATER;
            // Diagonal inferior iquierda.
            if ( hitPosition->row > 0 && hitPosition->column > 0
            && ( *shotsGrid )[ hitPosition->row - 1 ][ hitPosition->column - 1 ] == GAME_GRID_NULL )
                ( *shotsGrid )[ hitPosition->row - 1 ][ hitPosition->column - 1 ] = GAME_GRID_WATER;
            // Diagonal inferior derecha.
            if ( hitPosition->row > 0 && hitPosition->column < GAME_GRID_COLS - 1
            && ( *shotsGrid )[ hitPosition->row - 1 ][ hitPosition->column + 1 ] == GAME_GRID_NULL )
                ( *shotsGrid )[ hitPosition->row - 1 ][ hitPosition->column + 1 ] = GAME_GRID_WATER;
        break;
        // Imposible, FATAL ERROR -> RESUME.
        default:
            consoleLog( "\n aiWaterFill::UNDEFINED DIRECTION!" );
            if ( _Debug_Mode_ ) printf( "\n aiWaterFill::direction = %d", direction );
            consoleLog( "" );
        break;
    }
    if ( _Debug_Mode_ ) {
        clearConsole( );
        printf( "\n\t Tiros de la IA despu%cs de rellenar", LOWERCASE_E );
        printGameGrid( *&shotsGrid, 10, 5 );
        getche( );
    }
}
/////////////////////////////////////////////////////////////
void aiController( GameAI *ai ) {
    unsigned short int prevent = 0;
    bool invalidDirection, invalidRandomPosition;
    GameGridPosition position = { 0, 0 };
    // Cambios de estado en base al ultimo tiro.
    switch ( ai->shotType ) {
        case SHOT_HIT:
            consoleLog( "\n aiController::ai->shotType = SHOT_HIT" );
            // Si la IA acierta se cambia su estado a modo OBJETIVO.
            if ( ai->aiMode == HUNT_MODE ) {
                consoleLog( "\n aiController::ai->aiMode = TARGET_MODE" );
                ai->aiMode = TARGET_MODE;
                ai->firstHitPosition.row = ai->position.row;
                ai->firstHitPosition.column = ai->position.column;
                ai->hitPosition.row = ai->firstHitPosition.row;
                ai->hitPosition.column = ai->firstHitPosition.column;
             // En caso de que la IA haya acertado dos veces se establece una dirección de tiro.
             } else {
                // Fija la posición de tiro a la última establecida.
                ai->hitPosition.row = ai->position.row;
                ai->hitPosition.column = ai->position.column;
                // Fija la dirección de tiro a la última establecida.
                ai->hitDirection = ai->direction;
                consoleLog( "\n aiController::ai->hitDirection = ai->direction" );
                if ( _Debug_Mode_ ) printf( "\n aiController::ai->hitDirection = %d", ai->hitDirection );
                // Rellena de agua los laterales a partir de la dirección.
                consoleLog( "\n aiController::aiWaterFill( &ai->shotsGrid, &ai->position, &ai->hitPosition, &ai->hitDirection, true )" );
                aiWaterFill( &ai->shotsGrid, &ai->firstHitPosition, &ai->hitPosition, ai->hitDirection, false );
             }
        break;
        case SHOT_SUNKEN:
            // Fija la dirección de tiro a la última establecida siempre y cuando la IA, no haya acertado
            // a un barco, de una sola posición en modo cazador.
            if ( ai->aiMode != HUNT_MODE )
                ai->hitDirection = ai->direction;
            else ai->hitDirection = DIRECTION_NULL;
            consoleLog( "\n aiController::ai->shotType = SHOT_SUNKEN" );
            // Rellena de agua los laterales a partir de la dirección.
            consoleLog( "\n aiController::aiWaterFill( &ai->shotsGrid, &ai->position, &ai->hitPosition, &ai->hitDirection, true )" );
            aiWaterFill( &ai->shotsGrid, &ai->firstHitPosition, &ai->position, ai->hitDirection, true );
            // Si la IA hunde el barco, se cambia su estado a modo CAZADOR.
            ai->aiMode = HUNT_MODE;
            ai->direction = DIRECTION_NULL;
            ai->hitDirection = DIRECTION_NULL;
            ai->hitPosition.row = 0;
            ai->hitPosition.column = 0;
            ai->firstHitPosition.row = 0;
            ai->firstHitPosition.column = 0;
        break;
        case SHOT_MISS:
            consoleLog( "\n aiController::ai->shotType = SHOT_MISS" );
            // En el caso de que la IA esté en modo OBJETIVO.
            if ( ai->aiMode == TARGET_MODE ) {
                // Si la dirección de tiro que se estableció no funcinó, se invierte la dirección, por lo que quiere decir,
                // que el primer tiro en el blanco, no dió en uno de los dos extremos del barco, sino que dió en una de las
                // posiciones intermedias.
                switch ( ai->hitDirection ) {
                    case DIRECTION_TOP:    ai->hitDirection = DIRECTION_BOTTOM; break;
                    case DIRECTION_LEFT:   ai->hitDirection = DIRECTION_RIGHT;  break;
                    case DIRECTION_BOTTOM: ai->hitDirection = DIRECTION_TOP;    break;
                    case DIRECTION_RIGHT:  ai->hitDirection = DIRECTION_LEFT;   break;
                    default: break;
                }
                // las posiciones de tiro se invierten, ya que la el último tiro al blanco es uno de los extremos del blanco.
                if ( ai->hitDirection != DIRECTION_NULL ) {
                    consoleLog( "\n aiController::SWITCH ai->hitDirection" );
                    // Almacenamiento temporal.
                    position.row = ai->hitPosition.row;
                    position.column = ai->hitPosition.column;
                    // Inversión de las posiciones.
                    ai->hitPosition.row = ai->firstHitPosition.row;
                    ai->hitPosition.column = ai->firstHitPosition.column;
                    ai->firstHitPosition.row = position.row;
                    ai->firstHitPosition.column = position.column;
                    // Reset de la posición temporal.
                    position.row = 0;
                    position.column = 0;
                }
            }
        break;
        default: break;
    }
    // Decisiones en base al modo actual de la IA.
    switch( ai->aiMode ) {
        case HUNT_MODE:
            consoleLog( "\n aiController::switch case HUNT_MODE" );
            // Disparos de forma aleatoria en posiciones no repetidas.
            //do {
                do {
                    position.row = rand( ) % GAME_GRID_ROWS;
                    position.column = rand( ) % GAME_GRID_COLS;
                    invalidRandomPosition = validateAIRandomPosition( &ai->shotsGrid, &position, &ai->remainingShips );
                    // Utilizado en caso de dead loop.
                    prevent++;
                    if ( prevent > 600 ) return;
                } while ( !invalidRandomPosition );
            //} while ( ai->shotsGrid[ position.row ][ position.column ] != GAME_GRID_NULL );
        break;
        case TARGET_MODE:
             consoleLog( "\n aiController::switch case TARGET_MODE" );
            // Disparos en base a las resoluciones.
            do {
                invalidDirection = false;
                position.row = ai->hitPosition.row;
                position.column = ai->hitPosition.column;
                // Si no se ha obtenido una dirección de disparo, se obtiene una de forma aleatoria.
                // En caso contrario se basa en la dirección de tiro.
                consoleLog( "\n aiController::position.column = ai->hitPosition.column" );
                if ( _Debug_Mode_ ) printf( "\n aiController::ai->hitDirection = %c%c",
                                            GAME_GRID_ROWS_ENUMERATION[ position.row ], GAME_GRID_COLS_ENUMERATION[ position.column ]);
                if ( ai->hitDirection == DIRECTION_NULL ) {
                    ai->direction = rand( ) % 4;
                    consoleLog( "\n aiController::ai->direction = rand( ) % 4" );
                } else {
                    ai->direction = ai->hitDirection;
                    consoleLog( "\n aiController::ai->direction = ai->hitDirection" );
                }
                if ( _Debug_Mode_ ) printf( "\n aiController::ai->direction = %d", ai->direction );
                consoleLog( "" );
                switch ( ai->direction ) {
                    case DIRECTION_TOP:
                        // En caso de overflow del tablero.
                        consoleLog( "\n aiController::DIRECTION_TOP" );
                        if ( position.row == GAME_GRID_ROWS - 1 ) {
                            consoleLog( "\n aiController::OVERFLOW TOP" );
                            invalidDirection = true;
                            // Se invierte la dirección.
                            if ( ai->hitDirection == DIRECTION_TOP ) {
                                consoleLog( "\n aiController::SWITCH ai->hitDirection = DIRECTION_BOTTOM" );
                                ai->hitDirection = DIRECTION_BOTTOM;
                                // la posición de tiro a tener en cuenta pasará a ser la del primer tiro que dió en el blanco.
                                ai->hitPosition.row = ai->firstHitPosition.row;
                                ai->hitPosition.column = ai->firstHitPosition.column;
                            }
                        } else if ( validateAIRandomDirection( &ai->shotsGrid, &position, &ai->remainingShips, ai->direction ) )
                            position.row++;
                        else invalidDirection = true;
                    break;
                    case DIRECTION_LEFT:
                        consoleLog( "\n aiController::DIRECTION_LEFT" );
                        // En caso de overflow del tablero.
                        if ( position.column == 0 ) {
                            consoleLog( "\n aiController::OVERFLOW LEFT" );
                            invalidDirection = true;
                            // Se invierte la dirección.
                            if ( ai->hitDirection == DIRECTION_LEFT ) {
                                consoleLog( "\n aiController::SWITCH ai->hitDirection = DIRECTION_RIGHT" );
                                ai->hitDirection = DIRECTION_RIGHT;
                                // la posición de tiro a tener en cuenta pasará a ser la del primer tiro que dió en el blanco.
                                ai->hitPosition.row = ai->firstHitPosition.row;
                                ai->hitPosition.column = ai->firstHitPosition.column;
                            }
                        } else if ( validateAIRandomDirection( &ai->shotsGrid, &position, &ai->remainingShips, ai->direction ) )
                            position.column--;
                        else invalidDirection = true;
                    break;
                    case DIRECTION_BOTTOM:
                        consoleLog( "\n aiController::DIRECTION_BOTTOM" );
                        // En caso de overflow del tablero.
                        if ( position.row == 0 ) {
                            consoleLog( "\n aiController::OVERFLOW BOTTOM" );
                            invalidDirection = true;
                            // Se invierte la dirección.
                            if ( ai->hitDirection == DIRECTION_BOTTOM ) {
                                consoleLog( "\n aiController::SWITCH ai->hitDirection = DIRECTION_TOP" );
                                ai->hitDirection = DIRECTION_TOP;
                                // la posición de tiro a tener en cuenta pasará a ser la del primer tiro que dió en el blanco.
                                ai->hitPosition.row = ai->firstHitPosition.row;
                                ai->hitPosition.column = ai->firstHitPosition.column;
                            }
                        } else if ( validateAIRandomDirection( &ai->shotsGrid, &position, &ai->remainingShips, ai->direction ) )
                            position.row--;
                        else invalidDirection = true;
                    break;
                    case DIRECTION_RIGHT:
                        consoleLog( "\n aiController::DIRECTION_RIGHT" );
                        // En caso de overflow del tablero.
                        if ( position.column == GAME_GRID_COLS - 1 ) {
                            consoleLog( "\n aiController::OVERFLOW RIGHT" );
                            invalidDirection = true;
                            // Se invierte la dirección.
                            if ( ai->hitDirection == DIRECTION_RIGHT ) {
                                consoleLog( "\n aiController::SWITCH ai->hitDirection = DIRECTION_RIGHT" );
                                ai->hitDirection = DIRECTION_LEFT;
                                // la posición de tiro a tener en cuenta pasará a ser la del primer tiro que dió en el blanco.
                                ai->hitPosition.row = ai->firstHitPosition.row;
                                ai->hitPosition.column = ai->firstHitPosition.column;
                            }
                        } else if ( validateAIRandomDirection( &ai->shotsGrid, &position, &ai->remainingShips, ai->direction ) )
                            position.column++;
                        else invalidDirection = true;
                    break;
                    default: break;
                }
                // En caso de que dicha posición ya se haya resuelto anteriormente, se repite todo el proceso.
                if ( ( ai->shotsGrid )[ position.row ][ position.column ] != GAME_GRID_NULL ) {
                    invalidDirection = true;
                    // En caso de que se haya determinado una dirección de tiro, y la dirección marque una posición ya resuelta,
                    // se invierte la dirección de tiro, debido a que dicha posición es agua.
                    if ( ai->aiMode == TARGET_MODE ) {
                        // Si la dirección de tiro que se estableció no funcinó, se invierte la dirección, por lo que quiere decir,
                        // que el primer tiro en el blanco, no dió en uno de los dos extremos del barco, sino que dió en una de las
                        // posiciones intermedias.
                        switch ( ai->hitDirection ) {
                            case DIRECTION_TOP:    ai->hitDirection = DIRECTION_BOTTOM; break;
                            case DIRECTION_LEFT:   ai->hitDirection = DIRECTION_RIGHT;  break;
                            case DIRECTION_BOTTOM: ai->hitDirection = DIRECTION_TOP;    break;
                            case DIRECTION_RIGHT:  ai->hitDirection = DIRECTION_LEFT;   break;
                            default: break;
                        }
                        // las posiciones de tiro se invierten, ya que la el último tiro al blanco es uno de los extremos del blanco.
                        if ( ai->hitDirection != DIRECTION_NULL ) {
                            consoleLog( "\n aiController::SWITCH ai->hitDirection" );
                            // Almacenamiento temporal.
                            position.row = ai->hitPosition.row;
                            position.column = ai->hitPosition.column;
                            // Inversión de las posiciones.
                            ai->hitPosition.row = ai->firstHitPosition.row;
                            ai->hitPosition.column = ai->firstHitPosition.column;
                            ai->firstHitPosition.row = position.row;
                            ai->firstHitPosition.column = position.column;
                            // Reset de la posición temporal.
                            position.row = 0;
                            position.column = 0;
                        }
                    }
                }
                // Utilizado en caso de dead loop.
                prevent++;
                if ( prevent > 300 ) {
                    ai->aiMode = HUNT_MODE;
                    ai->hitDirection = DIRECTION_NULL;
                    ai->hitPosition.row = 0;
                    ai->hitPosition.column = 0;
                    ai->firstHitPosition.row = 0;
                    ai->firstHitPosition.column = 0;
                    do {
                        position.row = rand( ) % GAME_GRID_ROWS;
                        position.column = rand( ) % GAME_GRID_COLS;
                    } while ( ai->shotsGrid[ position.row ][ position.column ] != GAME_GRID_NULL );
                    return;
                }
            } while ( invalidDirection );
        break;
        default: break;
    }
    ai->position.row = position.row;
    ai->position.column = position.column;
}
/////////////////////////////////////////////////////////////
void saveGame( GameStructure *gameStructure ) {
    FILE* saveFile = fopen( concatenate( GAMESAVE_FILE_DIRECTORY, GAMESAVE_FILE_NAME ), "wb" );
    if ( saveFile != NULL ) {
        fwrite( *&gameStructure, sizeof( GameStructure ), 1, saveFile );
        fclose( saveFile );
    } else throwError( GAME_ERROR_UNABLE_TO_SAVE_GAME );
}
/////////////////////////////////////////////////////////////
bool hasGameSave( void ) {
    FILE* saveFile = fopen( concatenate( GAMESAVE_FILE_DIRECTORY, GAMESAVE_FILE_NAME ), "rb" );
    if ( saveFile != NULL ) {
        fclose( saveFile );
        return true;
    }
    return false;
}
/////////////////////////////////////////////////////////////
bool loadGame( GameStructure *gameStructure ) {
    FILE* saveFile = fopen( concatenate( GAMESAVE_FILE_DIRECTORY, GAMESAVE_FILE_NAME ), "rb" );
    if ( saveFile != NULL ) {
        fread( *&gameStructure, sizeof( GameStructure ), 1, saveFile );
        fclose( saveFile );
        return true;
    } else {
        clearConsole( );
        printStringWithColor( "\n No se ha encontrado ningun juego guardado.\n", GAME_COLOR_GREEN );
        printContinue( );
    }
    return false;
}
/////////////////////////////////////////////////////////////
void gameController( GameStructure *gameStructure, bool gameLoaded ) {
    bool
        validShot,  playerShot = false, aiShot = false, exit = false;
    short
        line, gridLine, column;
    unsigned short int shipSize;
    // Inicializa la semilla random. Necesario para el posterior uso de la funcion 'rand()'.
    srand( ( unsigned )time( NULL ) );
    // Si se ha empezado un juego nuevo.
    if ( !gameLoaded ) {
        /************************
         *** INICIALIZACIONES ***
         ************************/
        // Cambio de fase a 'INICIALIZACIÓN'.
        gameStructure->gamePhase           = GAME_INITIALIZATION;
        gameStructure->ai.aiMode           = HUNT_MODE;
        gameStructure->ai.shotType         = SHOT_INVALID;
        gameStructure->ai.hitDirection     = DIRECTION_NULL;
        gameStructure->player.ships        = GAME_SHIP_TOTAL_COUNT;
        gameStructure->ai.ships            = GAME_SHIP_TOTAL_COUNT;
        gameStructure->gameOver            = false;
        gameStructure->scoreMultiplier     = 1;
        gameStructure->player.score        = 0;
        gameStructure->player.shots        = 0;
        gameStructure->ai.shots            = 0;
        gameStructure->player.hits         = 0;
        gameStructure->ai.hits             = 0;
        gameShipsInitialization( &gameStructure->player.remainingShips );
        gameShipsInitialization( &gameStructure->ai.remainingShips );
        gameGridInitialization( &gameStructure->player.grid,         GAME_GRID_WATER );
        gameGridInitialization( &gameStructure->ai.grid,             GAME_GRID_WATER );
        gameGridInitialization( &gameStructure->player.shotsGrid,    GAME_GRID_NULL );
        gameGridInitialization( &gameStructure->ai.shotsGrid,        GAME_GRID_NULL );

        // En caso de no tener el modo debug activado, obtiene el nombre del jugador, no permite la longitud 0.
        if ( !_Debug_Mode_ )
            getPlayerName( gameStructure->player.name );
        else strcpy( gameStructure->player.name, "DEBUGGER" );
        /***************************************
         *** ALGORITMOS DEL NUCLEO DEL JUEGO ***
         ***************************************/
        // Cambio de fase a 'COLOCACIÓN DE BARCOS DEL JUGADOR'.
        gameStructure->gamePhase = PLAYER_SHIPS_ALLOCATION;
        // Si el usuario tiene activado el modo aleatorio o debug.
        if ( _Debug_Mode_ || gameStructure->playerShipsRandom )
            setRandomGrid( &gameStructure->player.grid );
        else if ( !setPlayerGrid( &gameStructure->player.grid ) )
            return;
        // Clona el tablero del jugador al tablero de impresión.
        cloneGrid( &gameStructure->printerGrid, &gameStructure->player.grid );
        // Cambio de fase a 'COLOCACIÓN DE BARCOS DE LA IA'.
        gameStructure->gamePhase = AI_SHIPS_ALLOCATION;
        setRandomGrid( &gameStructure->ai.grid );
        // SOLO EN CASO DE QUE EL MODO DEBUG ESTÉ ACTIVADO, SE MOSTRARÁ EL TABLERO DE LA IA ( Necesario para hacer las respectivas pruebas ).
        if ( _Debug_Mode_ )
            gameStructure->gamePhase = AI_SHOOT;
        else {
            // Decide de forma aleatoria quien empieza a disparar.
            if ( rand( ) % 2 == 0 )
                gameStructure->gamePhase = PLAYER_SHOOT;
            else gameStructure->gamePhase = AI_SHOOT;
            clearConsole( );
            printf( "\n %s EMPIEZA LA PARTIDA", gameStructure->gamePhase == PLAYER_SHOOT ? gameStructure->player.name : "LA IA" );
            printContinue( );
        }
    }
    if ( _Debug_Mode_ ) {
        clearConsole( );
        printf( "\n\t Barcos de la IA\n" );
        getConsoleCursorPosition( &column, &line );
        printGameGrid( &gameStructure->ai.grid, 10, line );
        printf( "\n\n\t Barcos del Jugador\n" );
        getConsoleCursorPosition( &column, &line );
        printGameGrid( &gameStructure->player.grid, 10, line );
        printf( "\n\n\t Tiros de la IA\n" );
        getConsoleCursorPosition( &column, &line );
        printGameGrid( &gameStructure->ai.shotsGrid, 10, line );
        printContinue( );
    }
    printGame( *&gameStructure, playerShot && aiShot );
    // Bucle de disparos.
    do {
        // Turnos.
        switch( gameStructure->gamePhase ) {
            case PLAYER_SHOOT:
                 // SOLO EN CASO DE QUE EL MODO DEBUG ESTÉ ACTIVADO, SE OMITIRÁ EL TURNO DEL JUGADOR ( Necesario para hacer las respectivas pruebas ).
                if ( _Debug_Mode_ ) {
                    gameStructure->gamePhase = AI_SHOOT;
                    break;
                }
                // Disparo del jugador.
                do {
                    // Si el jugador ha disparado correctamente se procede a la resolución.
                    do {
                        printGame( *&gameStructure, playerShot && aiShot );
                        validShot = getPlayerShoot( &gameStructure->player.position, &exit );
                        if ( exit ) {
                            saveGame( *&gameStructure );
                            return;
                        }
                        if ( !validShot ) {
                            printStringWithColor( "\n La celda introducida no es correcta.", GAME_COLOR_RED );
                            printContinue( );
                        }
                    } while ( !validShot );
                    gameStructure->player.shotType = shootController( &gameStructure->ai.grid, &gameStructure->player.shotsGrid, &gameStructure->player.position, &shipSize );
                    if ( gameStructure->player.shotType == SHOT_INVALID ) {
                        printStringWithColor( "\n No se puede repetir una misma celda.", GAME_COLOR_RED );
                        printContinue( );
                    }
                } while ( gameStructure->player.shotType == SHOT_INVALID );
                // Incrementa los disparos realizados por el jugador.
                playerShot = true;
                gameStructure->player.shots++;
                clearConsole( );
                // Incrementa el número de disparos acertados efectuados por el jugador.
                if ( gameStructure->player.shotType == SHOT_SUNKEN || gameStructure->player.shotType == SHOT_HIT ) {
                    gameStructure->player.hits++;
                    gameStructure->scoreMultiplier++;
                }
                // Dependiendo del resultado del disparo del jugador.
                switch ( gameStructure->player.shotType ) {
                    case SHOT_HIT: printf( "\n TOCADO!\n" ); break;
                    case SHOT_SUNKEN:
                        gameStructure->ai.ships--;
                        gameStructure->player.score += ( int )( 1 / shipSize ) * gameStructure->scoreMultiplier;
                        // Actualiza el número de barcos restantes que le queda por hundir al jugador.
                        updateRemainingShips( &gameStructure->player.remainingShips, shipSize );
                        printf( "\n TOCADO Y HUNDIDO!\n Barco de longitud: %d, Restantes: %d", shipSize, gameStructure->ai.ships );
                    break;
                    case SHOT_MISS:
                        // Si el disparo falla cambio de fase a 'AL TURNO DE LA IA'.
                        gameStructure->scoreMultiplier = 1;
                        gameStructure->gamePhase = AI_SHOOT;
                        printf( "\n AGUA!\n TURNO DE LA IA.\n" );
                    break;
                    default: break;
                }
                printContinue( );
            break;
            case AI_SHOOT:
                aiController( &gameStructure->ai );
                gameStructure->ai.shotType = shootController( &gameStructure->player.grid, &gameStructure->ai.shotsGrid, &gameStructure->ai.position, &shipSize );
                aiShot = true;
                gameStructure->ai.shots++;
                // Cambio del estado del tablero de impresion en base al disparo de la IA.
                if ( gameStructure->ai.shotType == SHOT_SUNKEN || gameStructure->ai.shotType == SHOT_HIT ) {
                    // Incrementa el número de disparos acertados efectuados por la IA.
                    gameStructure->ai.hits++;
                    gameStructure->scoreMultiplier++;
                    ( gameStructure->printerGrid )[ gameStructure->ai.position.row ][ gameStructure->ai.position.column ] = GAME_GRID_DAMAGED;
                    if ( gameStructure->ai.shotType == SHOT_SUNKEN )
                        updateDamaGedShipToShunken( &gameStructure->printerGrid, &gameStructure->ai.position );
                } else
                    ( gameStructure->printerGrid )[ gameStructure->ai.position.row ][ gameStructure->ai.position.column ] = GAME_GRID_AI_MISS;
                // Imprime el tablero una vez la IA ha movido.
                printGame( *&gameStructure, playerShot && aiShot );
                printf( "\n La IA DISPAR%c EN LA POSICI%cN %c%c", UPPERCASE_O, UPPERCASE_O,
                       GAME_GRID_ROWS_ENUMERATION[ gameStructure->ai.position.row ], GAME_GRID_COLS_ENUMERATION[ gameStructure->ai.position.column ] );
                // Dependiendo del resultado del disparo de la IA.
                switch ( gameStructure->ai.shotType ) {
                    case SHOT_HIT: printf( ", TOCADO!\n" ); break;
                    case SHOT_SUNKEN:
                        gameStructure->player.ships--;
                        gameStructure->player.score -= ( int )( ( 1 / shipSize ) * gameStructure->scoreMultiplier );
                        if ( gameStructure->player.score < 0 )
                            gameStructure->player.score = 0;
                        printf( ", TOCADO Y HUNDIDO!" );
                        // Actualiza el número de barcos restantes que le queda por hundir a la IA.
                        updateRemainingShips( &gameStructure->ai.remainingShips, shipSize );
                        printf( "\n Barco de longitud: %d, Restantes: %d\n", shipSize, gameStructure->player.ships );
                    break;
                    case SHOT_MISS:
                        // Si el disparo falla cambio de fase a 'AL TURNO DEL JUGADOR'.
                        gameStructure->gamePhase = PLAYER_SHOOT;
                        gameStructure->scoreMultiplier = 1;
                        printf( ", AGUA!\n TURNO DEL JUGADOR.\n" );
                    break;
                    default: break;
                }
                // SOLO EN CASO DE QUE EL MODO DEBUG ESTÉ ACTIVADO, SE MOSTRARÁ EL TABLERO DE TIROS LA IA ( Necesario para hacer las respectivas pruebas ).
                if ( _Debug_Mode_ ) {
                    clearConsole( );
                    printf( "\n\t Tiros de la IA \n\t [ Tiro: %c%d ]\n\t [ Numero: %d ] [ Aciertos: %d ]",
                       GAME_GRID_ROWS_ENUMERATION[ gameStructure->ai.position.row ], gameStructure->ai.position.column, gameStructure->ai.shots, gameStructure->ai.hits );
                    printGameGrid( &gameStructure->ai.shotsGrid, 10, 5 );
                }
                printContinue( );
            break;
            default: break;
        }
        // Imprime el tablero del juego después de cada jugada.
        printGame( *&gameStructure, playerShot && aiShot );
        // SOLO EN CASO DE QUE EL MODO DEBUG ESTE ACTIVADO SE PODRÁ SALIR DE LA PARTIDA PULSANDO ESC.
        if ( _Debug_Mode_ && getch( ) == KEYCODE_ESC ) return;
        // Salva el juego después de cada jugada.
        else saveGame( *&gameStructure );
        // Si se han hundido todos los barcos de alguno de los dos jugadores, se termina el juego.
        if ( gameStructure->ai.ships == 0 || gameStructure->player.ships == 0 ) {
            gameStructure->gameOver = true;
            // Elimina el archivo de guardado de la partida siempre y cuando no se encuentre en modo debug.
            if ( !_Debug_Mode_ )
                remove( concatenate( GAMESAVE_FILE_DIRECTORY, GAMESAVE_FILE_NAME ) );
            clearConsole( );
            printMessage( "FIN DEL JUEGO",
                ( gameStructure->ai.ships == 0 ) ? "Felicidades, has ganado la partida." : "Lo sentimos, la IA ha ganado la partida.", 0, 1 );
            // Imprime el resultado.
            printf( "\n\n" );
            getConsoleCursorPosition( &column, &gridLine );
            printGameGrid( &gameStructure->ai.grid, column, gridLine );
            getConsoleCursorPosition( &column, &line );
            printGameGrid( &gameStructure->player.shotsGrid, column + 5, gridLine );
            printf( "\n\n PUNTUACI%cN FINAL: %d\n", UPPERCASE_O, gameStructure->player.score );
            printContinue( );
        }
    } while ( !gameStructure->gameOver );
}
