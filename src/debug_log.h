/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Provides functions for logging debug    
 *                 : information to a given output.
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

#ifndef __DEBUG_LOG_H 
#define __DEBUG_LOG_H
/* (cschol, 2008: header guard) */

#include <stdio.h>

#define LOG_LEVEL_ERROR    0
#define LOG_LEVEL_WARNING  1
#define LOG_LEVEL_VERBOSE  2

void debugLog( int logLevel, 
                const char* message_format, ... );
int  getDebugLogLevel(  void );
int  setDebugLogLevel(  int level );
bool setDebugLogOutput( FILE* file );

#endif

/* --------------------- Works Cited -------------------- */
/* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 * cschol. (2008). "Organization of C files: Answer."
 *      Stackoverflow.  Retrieved from https://stackoverflow
 *      .com/questions/47919/organization-of-c-files on 2022
 *      June 03.
 */
