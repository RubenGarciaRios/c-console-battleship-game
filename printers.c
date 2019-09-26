/////////////////
/// CABECERAS ///
/////////////////
#include "printers.h"
/////////////////
/// FUNCIONES ///
/////////////////
void clearConsole( void ) {
#ifdef _WIN32
    //system( "cls" );
    HANDLE consoleHandler = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD coordScreen = { 0, 0 };
    DWORD charsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD consoleSize;
    if( !GetConsoleScreenBufferInfo( consoleHandler, &csbi ) )
      return;
    consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    if ( !FillConsoleOutputCharacter( consoleHandler, (TCHAR) ' ', consoleSize, coordScreen, &charsWritten ) )
      return;
    if ( !GetConsoleScreenBufferInfo( consoleHandler, &csbi ) )
      return;
    if( !FillConsoleOutputAttribute( consoleHandler, csbi.wAttributes, consoleSize, coordScreen, &charsWritten ) )
      return;
    SetConsoleCursorPosition( consoleHandler, coordScreen );
#endif
}
/////////////////////////////////////////////////////////////
void getConsoleCursorPosition( short *column, short *line ) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if ( !GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi ) ) {
        *column = -1;
        *line = -1;
    } else {
        *column = csbi.dwCursorPosition.X;
        *line = csbi.dwCursorPosition.Y;
    }
#endif
}
/////////////////////////////////////////////////////////////
void setConsoleCursorPosition( short column, short line ) {
#ifdef _WIN32
    COORD coordinates;
    getConsoleCursorPosition( &coordinates.X, &coordinates.Y );
    if ( column >= 0 )
        coordinates.X = column;
    if ( line >= 0 )
        coordinates.Y = line;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coordinates );
#endif
}
/////////////////////////////////////////////////////////////
void printStringWithColor( const char* string, int color ) {
#ifdef _WIN32
    HANDLE consoleHandler = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD defaultWordAtributes;
    // Obtiene el color de la consola que hay por defecto.
    GetConsoleScreenBufferInfo( consoleHandler, &consoleInfo );
    defaultWordAtributes = consoleInfo.wAttributes;
    // Aplica el color establecido.
    SetConsoleTextAttribute( consoleHandler, color );
    printf( "%s", string );
    // Restablece el color de la consola al obtenido por defecto.
    SetConsoleTextAttribute( consoleHandler, defaultWordAtributes );
#endif
}
/////////////////////////////////////////////////////////////
void printMessage( const char *title, const char *message, short column, short line ) {
    char
        *padding = "  ";
    size_t
        n = strlen( title ) + strlen( padding ) * 4, i = 0;
    char *separator = malloc( n * sizeof( char ) );
    setConsoleCursorPosition( column, line );
    // Separador del mensaje.
    strcpy( separator, "" );
    for( i = 0; i < n; i++ )
        strcat( separator, "/" );
    printf( "%s", separator ); line++;
    setConsoleCursorPosition( column, line );
    printf( "//%s", padding );
    // Titulo del mensaje.
    printStringWithColor( *&title, GAME_COLOR_GREEN );
    printf( "%s//", padding ); line++;
    setConsoleCursorPosition( column, line );
    // Cuerpo del mensaje.
    printf( "%s", separator ); line++; line++;
    setConsoleCursorPosition( column, line );
    printf( "%s%s", padding, message ); line++; line++;
    setConsoleCursorPosition( column, line );
    printf( "%s", separator );
}
/////////////////////////////////////////////////////////////
void printContinue( void ) {
    printStringWithColor( "\n Pulse una tecla para continuar.\n", GAME_COLOR_YELLOW );
    getch( );
}
/////////////////////////////////////////////////////////////
bool confirm( const char *title, const char *message ) {
    char key;
    // Se repite mientras que el usuario no responda correctamente.
    do {
        clearConsole( );
        printMessage( *&title, *&message, 0, 2 );
        printf( "\n\nPulse las teclas:\n 'S' para confirmar. \n 'N' para cancelar.\n" );
        key = getch( );
    } while ( key != KEYCODE_N && key != KEYCODE_S );
    return key == KEYCODE_S ? true : false;
}
/////////////////////////////////////////////////////////////
void progressBar( const char* title, unsigned int progressBarwidth, unsigned int total, unsigned int current ) {
    unsigned int
        i, progress = ( int )( current * 100 / total ), progressWidth = ( int )( current * progressBarwidth / total );
    clearConsole( );
    printf( "\n %s \n[", title );
    for( i = 0; i < progressBarwidth; i++ )
        printf( "%c", i < progressWidth ? '#' : ' ' );
    printf( "] %d%%\n", progress );
}
/////////////////////////////////////////////////////////////
void throwError( const char* string ) {
    clearConsole( );
#ifdef _WIN32
    printStringWithColor( string, GAME_COLOR_RED );
    printContinue( );
#else
    printf( "\n%s", string );
    getche( );
#endif
    exit( EXIT_FAILURE );
}
/////////////////////////////////////////////////////////////
void printFileContent( const char* filePath ) {
    FILE* filePointer = fopen( filePath, "r" );
    int character;
    // Validación de la correcta apertura del fichero.
    if ( filePointer == NULL )
       throwError( GAME_ERROR_FILE_NOT_FOUND );
    while ( ( character = getc( filePointer ) ) != EOF )
        putchar( character );
    // Cierre del fichero una vez que se han leido su contenido.
    fclose( filePointer );
}
/////////////////////////////////////////////////////////////
void printGameGrid( GameGrid *gameGrid, short column, short line ) {
    // Reservado de memoria a 3 char más el caracter NULL (\0).
    char
       *enumerators[ ] = {
            GAME_GRID_ROWS_ENUMERATION,
            GAME_GRID_COLS_ENUMERATION
        }, cell[ 4 ];
    int color;
    unsigned short int
        i = 0, j = 0;
    // Bucle de impresión.
    for ( i = 0; i < GAME_GRID_ROWS; i++ ) {
        // Cabeceras.
        setConsoleCursorPosition( column + 1, line );
        if ( i == 0 ) {
            for ( j = 0; j < GAME_GRID_COLS; j++ )
                printf( " %c ", enumerators[ 1 ][ j ] );
            line++;
        }
        setConsoleCursorPosition( column, line );
        printf( "%c", enumerators[ 0 ][ i ] );
        // Celdas.
        for ( j = 0; j < GAME_GRID_COLS; j++ ) {
            // Dependiendo del tipo de celda
            switch( (*gameGrid)[ i ][ j ] ) {
                case GAME_GRID_AI_MISS:         color = GAME_COLOR_LIGHT_BLUE;  break;
                case GAME_GRID_WATER:           color = GAME_COLOR_BLUE;        break;
                case GAME_GRID_SHIP:            color = GAME_COLOR_LIGHT_GREEN; break;
                case GAME_GRID_DAMAGED:         color = GAME_LIGHT_COLOR_RED;   break;
                case GAME_GRID_SHUNKEN:         color = GAME_COLOR_RED;         break;
                case GAME_GRID_WRONG_POSITION:  color = GAME_COLOR_RED;         break;
                default:                        color = -1;                     break;
            }
            cell[ 0 ] = ' ';
            cell[ 1 ] = ( *gameGrid )[ i ][ j ];
            cell[ 2 ] = ' ';
            cell[ 3 ] = '\0';
            if ( color >= 0 )
                printStringWithColor( cell, color );
            else
                printf( cell );
       }
        line++;
    }
}
/////////////////////////////////////////////////////////////
void printGame( GameStructure *gameStructure, bool log ) {
    short
        marginLeft = 5, marginTop = 5, column = marginLeft, line = marginTop, padding;
    clearConsole( );
    printRemainingShips( &gameStructure->player.remainingShips );
    setConsoleCursorPosition( column, line );
    printf( "  BARCOS DE '%s'", gameStructure->player.name );
    line++; line++;
    printGameGrid( &gameStructure->printerGrid, column, line );
    getConsoleCursorPosition( &column, &line );
    line = marginTop;
    column += marginLeft;
    setConsoleCursorPosition( column, line );
    printf( "  MOVIMIENTOS DE '%s'", gameStructure->player.name );
    line++; line++;
    printGameGrid( &gameStructure->player.shotsGrid, column, line );
    padding = column;
    printf( "\n\n" );
    getConsoleCursorPosition( &column, &line );
    setConsoleCursorPosition( marginLeft, line );
    printf( " - TIROS IA: %d", gameStructure->ai.shots );
    setConsoleCursorPosition( padding, line );
    printf( " - TIROS '%s': %d", gameStructure->player.name, gameStructure->player.shots );
    line++;
    setConsoleCursorPosition( marginLeft, line );
    printf( " - ACIERTOS IA: %d", gameStructure->ai.hits );
    setConsoleCursorPosition( padding, line );
    printf( " - ACIERTOS '%s': %d", gameStructure->player.name, gameStructure->player.hits );
    if ( log ) {
        line++;
        setConsoleCursorPosition( marginLeft, line );
        printf( " - LA IA TIR%c EN: %c%c", UPPERCASE_O,
                GAME_GRID_ROWS_ENUMERATION[ gameStructure->ai.position.row ], GAME_GRID_COLS_ENUMERATION[ gameStructure->ai.position.column ] );
        setConsoleCursorPosition( padding, line );
        printf( " - '%s' TIR%c EN: %c%c", gameStructure->player.name, UPPERCASE_O,
                 GAME_GRID_ROWS_ENUMERATION[ gameStructure->player.position.row ], GAME_GRID_COLS_ENUMERATION[ gameStructure->player.position.column ] );
    }
    printf( "\n" );
}
/////////////////////////////////////////////////////////////
void printRemainingShips( GameShips *remainingShips ) {
    unsigned short int
        i = 0, j = 0;
    char ship[ 4 ];
    ship[ 0 ] = ' ';
    ship[ 1 ] = GAME_GRID_SHIP;
    ship[ 2 ] = ' ';
    ship[ 3 ] = '\0';
    printf( "\n" );
    // Imprime cada uno de los barcos con su número restante.
    printf( " BARCOS POR HUNDIR:\n\n " );
    for ( i = 0; i < GAME_SHIPS_TYPES; i++ ) {
         printf( "[" );
        for ( j = 0; j < ( *remainingShips )[ i ][ 1 ]; j++ )
            printStringWithColor( ship, GAME_COLOR_GREEN );
        printf( "]x%d ", ( *remainingShips )[ i ][ 0 ] );
    }
}
/////////////////////////////////////////////////////////////
int gameMenu(
    const char* title,
    const char* description,
    const char* cursor,
    Orientations orientation,
    unsigned short int padding,
    unsigned short int defaultOption,
    unsigned short int numberOfOptions,
    ...
) {
    va_list arguments;
    size_t
        n = strlen( title ), k = 0;
    int
        position, i = 0, selectedOption = defaultOption;
    char
        key, *separator = malloc ( ( n + 2 + padding * 2 ) * sizeof( char ) );
    // Bucle del menú.
    do {
        if ( ( key == KEYCODE_UP && orientation == VERTICAL ) || ( key == KEYCODE_LEFT && orientation == HORIZONTAL ) )
            ( selectedOption > 1 && selectedOption != 1 ) ? selectedOption-- : ( selectedOption = numberOfOptions );
        else if ( ( key == KEYCODE_DOWN && orientation == VERTICAL ) || ( key == KEYCODE_RIGHT && orientation == HORIZONTAL ) )
            ( selectedOption >= 1 && selectedOption != numberOfOptions ) ? selectedOption++ : ( selectedOption = 1);
        // Separador del menu.
        strcpy( separator, "" );
        for( k = 0; k < n + 2 + padding * 2; k++ )
            strcat( separator, "/" );
        // Limpia la consola.
        clearConsole( );
        // CABECERA.
        // Impresión de la cabecera del menú.
        printf( "\n%s\n//  ", separator );
        printStringWithColor( title, GAME_COLOR_GREEN );
        printf( "  //\n%s\n//\n//  %s\n//\n%s\n%s\n", separator, description, separator, ( orientation == VERTICAL ) ? "//" : "" );
        // OPCIONES.
        // Argumentos variables.
        va_start( arguments, numberOfOptions );
        for ( i = 1; i <= numberOfOptions; i++ ) {
            position = padding;
            if ( orientation == VERTICAL )
                printf( "//" );
            while( ( position-- ) > 0 )
                printf( " " );
            if( i == selectedOption ) {
                printf( "\b\b%s", cursor );
                printStringWithColor( va_arg( arguments, char * ), GAME_COLOR_RED );
            } else
                printf( "%s", va_arg( arguments, char * ) );
            ( orientation == VERTICAL ) ? ( ( i < numberOfOptions ) ? printf( "\n" ) : 0 ) : printf( "  " );
        }
        // Fin Argumentos variables.
        va_end( arguments );
        printf( "\n%s\n%s\n\n * Use las teclas:\n %s para moverse entre las opciones del men%c.\n 'ESCAPE' para volver.\n",
                ( orientation == VERTICAL ) ? "//" : "" ,
                separator,
                ( orientation == VERTICAL ) ? "'ARRIBA' y 'ABAJO'" : "'IZQUIERDA' y 'DERECHA'",
                LOWERCASE_U );
        // En caso de que se presione la tecla 'ESCAPE' se vuelve al estado anterior a la apertura del menú.
        if ( key == KEYCODE_ESC )
            return GAME_MENU_RETURN;
    } while ( ( key = getch( ) ) != KEYCODE_ENTER );
    return selectedOption;
}
/////////////////////////////////////////////////////////////
void printGameCredits( void ) {
    clearConsole( );
    printf( "\n UNIVERSIDAD REY JUAN CARLOS 2016-2017, INICIACI%cN A LA PROGRAMACI%cN", UPPERCASE_O, UPPERCASE_O );
    printf( "\n\n\tANALISIS Y ESTRUCTURACI%cN \n\n\t - Rub%cn Garc%ca R%cos", UPPERCASE_O, LOWERCASE_E, LOWERCASE_I, LOWERCASE_I );
    printf( "\n\n\tDESARROLLADORES\n\n\t - Rub%cn Garc%ca R%cos", LOWERCASE_E, LOWERCASE_I, LOWERCASE_I );
    printf( "\n\n\tTESTEO\n\n\t - Rub%cn Garc%ca R%cos", LOWERCASE_E, LOWERCASE_I, LOWERCASE_I );
    printf( "\n\n\tAGRADECIMIENTOS\n\n\t - Bel%cn Garc%ca R%cos", LOWERCASE_E, LOWERCASE_I, LOWERCASE_I );
    printContinue( );
}
