/////////////////
/// CABECERAS ///
/////////////////
#include "utils.h"
/////////////////
/// FUNCIONES ///
/////////////////
const char* concatenate( const char* start, const char* end ) {
    char* string;
    string = malloc( strlen( start ) + strlen( end ) + 1 );
    strcpy( string, start );
    strcat( string, end );
    return string;
}
/////////////////////////////////////////////////////////////
char* charToString( const char c ) {
    char string[ 2 ] = { c, '\0' };
    char* pointer = ( char* )malloc( sizeof( char ) * 2 );
    strcpy( pointer, string );
    return pointer;
}
/////////////////////////////////////////////////////////////
char *leftTrim( char *string ) {
    while( isspace( *string ) ) string++;
    return string;
}
/////////////////////////////////////////////////////////////
char *rightTrim( char *string ) {
    char* back = string + strlen( string );
    while( isspace( *--back ) );
    *( back + 1 ) = '\0';
    return string;
}
/////////////////////////////////////////////////////////////
char *trim( char *string ) { return rightTrim( leftTrim( string ) ); }
/////////////////////////////////////////////////////////////
void consoleLog( const char *message ) {
    if ( !_Debug_Mode_ ) return;
    printf( "%s", message );
    getche( );
}
