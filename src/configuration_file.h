/* Filename        : hello_world.h
 * Type of File    : C Source Code, Header
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : gcc hello_world.c -o hello_world
 *  and Run        : ./hello_world
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9]
 * [File Use: Stefano & Smith, 2009 ] */

/* https://www.programiz.com/c-programming/c-structures */

#ifndef __CONFIGURATION_FILE_H /* [guard modeled on cschol, 2008] */
#define __CONFIGURATION_FILE_H

#include <stdbool.h>

#include "command_line_args.h"

//typedef   int (*Operation)(int a , int b );
/*
struct commandLineOption {
    char* shortForm;
    char* longForm;
    char* description;
    char* dataType;
    char* currentValueString;
    bool (*setSetting)(const char*);
    };*/

int readConfigurationFile(FILE* file, 
  int commandLineOptionC, 
        struct commandLineOption options[]);

#endif
/* -------------------- Works Cited -------------------- */
/* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition.." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 */
