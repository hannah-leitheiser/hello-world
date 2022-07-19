/* Filename        : debug_log.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Provides functions for logging debug
 *                 : information to a given output.
 * ( Kernighan & Ritchie, 1988, p. 9: Comment Syntax ) */

#define _GNU_SOURCE  /* ( Brouwer, 2001, Synopsis )       */ 
#include <stdio.h>   /* ( Brouwer, 2001, Synopsis )       */ 
#include <stdbool.h> /* ( Jester-Young, 2010 )            */
#include <stdarg.h>  /* ( cppreference.com, 2020 )        */


#include "printf.h"      /* for nameStream() */
#include "hello_world.h" /* for DEBUG_LOG definition */

#include "debug_log.h"

/*
for reference

#define LOG_LEVEL_ERROR    0 
#define LOG_LEVEL_WARNING  1 
#define LOG_LEVEL_VERBOSE  2 
*/

FILE* debugLogOutput = NULL;
int debugLogLevel = LOG_LEVEL_ERROR;

char* logLevelString( int level );

/* ------------------ debugLog() -------------------------*/

void debugLog( int logLevel, 
       const char* message_format, ... ) {
    #ifdef DEBUG_LOG
    
    if(debugLogOutput && logLevel <= debugLogLevel) {

        char* levelString = logLevelString(logLevel);

        if(!levelString) {
            levelString = "???????";
        }

        fprintf( debugLogOutput, "Log:%s:", levelString);
        
        va_list argptr;
        va_start(argptr,message_format);
         /* ( cppreference.com, 2020, va_start, example ) */
        vfprintf( debugLogOutput,message_format, argptr);
        fprintf( debugLogOutput, "\n" );
        va_end(argptr);
         /* ( cppreference.com, 2020, va_start, example ) */
    }

    #endif
    return;
}

/* -------------- getDebugLogLevel() ---------------------*/

int getDebugLogLevel( void ) {
    char* levelString = logLevelString(debugLogLevel);
    if(levelString) {
        debugLog( LOG_LEVEL_VERBOSE, 
               "getDebugLogLevel():"
           "Log level %d:%s", debugLogLevel, levelString );
        return debugLogLevel;
    }
    else {
        debugLog( LOG_LEVEL_WARNING, 
            "getDebugLogLevel():"
            "Log level %d not recgonized.", debugLogLevel );
        return -1;
    }
}

/* ------------------ setDebugLogLevel() ---------------- */

int setDebugLogLevel( int level ) {
    char* levelString = logLevelString(level);
    if(levelString) {
        debugLogLevel = level;
        debugLog( LOG_LEVEL_VERBOSE, 
            "setDebugLogLevel():"
            "Log level set to %d:%s", 
                       debugLogLevel, levelString );
    }
    else {
        levelString = logLevelString(debugLogLevel);
        if (levelString ) {
            debugLog( LOG_LEVEL_WARNING, 
                  "setDebugLogLevel():"
                  "Log level %d not recgonized, "
                  "log level remains %d:%s.", 
                      level, debugLogLevel, levelString );
        }
        else {
            debugLog( LOG_LEVEL_WARNING, 
                  "setDebugLogLevel():"
                  "Log level %d not recgonized, "
                  "log level remains %d:??????.", 
                      level, debugLogLevel );
        }
    }
    return debugLogLevel;
}

/* ----------------- setDebugLogOutput() ---------------- */

bool setDebugLogOutput( FILE* file ) {
    if(file) {
        debugLogOutput = file;
        debugLog( LOG_LEVEL_VERBOSE, 
            "setDebugLogOutput():"
            "Log output stream set to %s.", 
                        nameStream( debugLogOutput ) );
        return true;
    }
    else {
        debugLog( LOG_LEVEL_WARNING, 
                "setDebugLogOutput():"
                "NULL file supplied, "
                "log output stream remains %s.", 
                       nameStream ( debugLogOutput ) );
        return false;
    }
}

/* ----------------- logLevelString() ------------------- */

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
            debugLog( LOG_LEVEL_WARNING, 
                   "logLevelString():"
                   "Log level %d not recgonized.", level );
        }
    return levelString; // may be NULL
}
/* --------------------- Works Cited -------------------- */
/* 
 * Brouwer, Andries. (2001). "asprintf(3) — Linux manual
 *      page." GNU Linux.  Retrieved from
 *      https://man7.org/linux/man-
 *      pages/man3/asprintf.3.html on 2022 June 25.
 * Jester-Young, Chris. (2010). "Using true and false in C:
 *      Answer." Stackoverflow.  Retrieved from
 *      https://stackoverflow.com/questions/2254075/using-
 *      true-and-false-in-c on 2022 June 18.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 */
