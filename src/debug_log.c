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

/* ( Karpov, 2008:
                  reviewed before writing this document ) */

/*
for reference, from debug_log.h:

#define LOG_LEVEL_ERROR    0 
#define LOG_LEVEL_WARNING  1 
#define LOG_LEVEL_VERBOSE  2 
*/

FILE* debugLogOutput = NULL;
int debugLogLevel = LOG_LEVEL_ERROR;


#ifdef DEBUG_LOG
char* logLevelString( int level );
#endif

/* ------------------ debugLog() -------------------------*/
/* Output appropriate debug messages to the appropriate
 * output.  Mute messages below debugLogLevel setting 
 * eg. mute VERBOSE when level is set to WARNING and above.
 */


#ifdef DEBUG_LOG
void debugLogPrintError();
#endif

void debugLog( int logLevel, 
       const char* message_format, ... ) {
    #ifdef DEBUG_LOG
    
    if(debugLogOutput && logLevel <= debugLogLevel) {

        char* levelString = logLevelString(logLevel);
        int printfReturn;

        if(!levelString) {
            levelString = "???????";
        }

        printfReturn = 
          fprintf( debugLogOutput, "Log:%s:", levelString );

        if(printfReturn < 0) {
            debugLogPrintError();
            return;
        }
        
        va_list argptr;
        va_start(argptr,message_format);
         /* ( cppreference.com, 2020, va_start, example ) */

        printfReturn = 
          vfprintf( debugLogOutput,message_format, argptr);

        if(printfReturn < 0) {
            va_end(argptr);
            debugLogPrintError();
            return;
        }

        printfReturn = fprintf( debugLogOutput, "\n" );

        if(printfReturn < 0) {    
            debugLogPrintError();
        }

        va_end(argptr);
         /* ( cppreference.com, 2020, va_start, example ) */
    }

    #endif
    return;
}

/* ------------- debugLogPrintError() ------------------- */


#ifdef DEBUG_LOG
bool debugLogErrorPrinted = false;

void debugLogPrintError() {
    /* let's not make too many of these */
    if(!debugLogErrorPrinted) {
        fprintf( stderr, 
              "Unable to print debug messages.\n"
              "Specified debug output file may not be "
              "writable by this program.\n" );
        debugLogErrorPrinted = true;
    }
    return;
}
#endif

/* -------------- getDebugLogLevel() -------------------- */

int getDebugLogLevel( void ) {
    #ifdef DEBUG_LOG
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
    #endif
    #ifndef DEBUG_LOG
    return -1;
    #endif
}

/* ------------------ setDebugLogLevel() ---------------- */

int setDebugLogLevel( int level ) {
    #ifdef DEBUG_LOG
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
    #endif
    #ifndef DEBUG_LOG
    return -1;
    #endif
}

/* ----------------- setDebugLogOutput() ---------------- */

bool setDebugLogOutput( FILE* file ) {
    #ifdef DEBUG_LOG
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
    #endif
    #ifndef DEBUG_LOG
    return false;
    #endif
}

/* ----------------- logLevelString() ------------------- */

#ifdef DEBUG_LOG
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
#endif

/* --------------------- Works Cited -------------------- */
/* 
 * Andrey Karpov. (2008). "Building of systems of automatic
 *      C/C++ code logging." PVS-Studio.  Retrieved from
 *      https://pvs-studio.com/en/blog/posts/a0023/ on 2022
 *      June 16.
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
 * cppreference.com. (2020). "va_list." cppreference.com.
 *      Retrieved from
 *      https://en.cppreference.com/w/c/variadic/va_list on
 *      2022 July 16.
 * cppreference.com. (2020). "va_start." cppreference.com.
 *      Retrieved from
 *      https://en.cppreference.com/w/c/variadic/va_start on
 *      2022 July 16.
 */
