/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : gcc hello_world.c -o hello_world
 *  and Run        : ./hello_world
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

#define _GNU_SOURCE
#include <stdio.h> /* [Kernighan & Ritchie, 1988, p. 6] */
#include <stdbool.h> /* https://stackoverflow.com/questions/2254075/using-true-and-false-in-c */
#include "debug_log.h"
#include "printf.h" /* for nameStream() */

/*
for reference

#define LOG_LEVEL_ERROR    0 
#define LOG_LEVEL_WARNING  1 
#define LOG_LEVEL_VERBOSE  2 
*/

FILE* debugLogOutput;
int debugLogLevel = LOG_LEVEL_VERBOSE;

char* logLevelString( int level ) {

    char* levelString = NULL;
    switch( level ) {
        case LOG_LEVEL_ERROR:
            levelString = "Error ";
            break;
        case LOG_LEVEL_WARNING:
            levelString = "Warning";
            break;
        case LOG_LEVEL_VERBOSE:
            levelString = "Verbose";
            break;
        default:
            debugLog( LOG_LEVEL_WARNING, "logLevelString():Log level %d not recgonized.", level );
        }
    return levelString; // may be NULL

}

void debugLog( int logLevel, const char* message_format, ... ) {
    
    if(debugLogOutput && logLevel <= debugLogLevel) {

        char* levelString = logLevelString(logLevel);

        if(!levelString) {
            levelString = "???????";
        }

        fprintf( debugLogOutput, "Log:%s:", levelString);
        
        va_list argptr;
        va_start(argptr,message_format);
        vfprintf( debugLogOutput,message_format, argptr);
        fprintf( debugLogOutput, "\n" );
    }
}


int getDebugLogLevel( void ) {
    char* levelString = logLevelString(debugLogLevel);
    if(levelString) {
        debugLog( LOG_LEVEL_VERBOSE, "getDebugLogLevel():Log level %d:%s", debugLogLevel, levelString );
        return debugLogLevel;
    }
    else {
        debugLog( LOG_LEVEL_WARNING, "getDebugLogLevel():Log level %d not recgonized.", debugLogLevel );
        return -1;
    }
}


int setDebugLogLevel( int level ) {
    char* levelString = logLevelString(level);
    if(levelString) {
        debugLogLevel = level;
        debugLog( LOG_LEVEL_VERBOSE, "setDebugLogLevel():Log level set to %d:%s", debugLogLevel, levelString );
    }
    else {
        levelString = logLevelString(debugLogLevel);
        if (levelString ) {
            debugLog( LOG_LEVEL_WARNING, "setDebugLogLevel():Log level %d not recgonized, log level remains %d:%s.", level, debugLogLevel, levelString );
        }
    }
    return debugLogLevel;
}

int setDebugLogOutput( FILE* file ) {
    if(file) {
        debugLogOutput = file;
        debugLog( LOG_LEVEL_VERBOSE, "setDebugLogOutput():Log output stream set to %s.", nameStream( debugLogOutput ) );
        return true;
    }
    else {
        debugLog( LOG_LEVEL_WARNING, "setDebugLogOutput():NULL file supplied, log output stream remains %s.", nameStream ( debugLogOutput ) );
        return false;
    }
}

/*  Works Cited:
 *  WG14. (2018).  Programming Languages -- C. 9899:202x (E).  ISO/IEC.
 *     Retrieved from https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf
 *     on 2022 June 03.
 *  Kernighan, Brian W. & Ritchie, Dennis M.  (1988).  The C Programming Language.  
 *     Second Edition.  Prentise Hall.  ISBN 0-13-110370-9. 
 *  Thompson, Keith.  2012.  "Should I return EXIT_SUCCESS or 0 
 *     from main()?: Answer."  Stack Overflow.  
 *     Retrieved from 
 *     https://stackoverflow.com/questions/8867871/should-i-return-exit-success-or-0-from-main
 *     on 2022 June 03.
 */
