/* Filename        : command_line_args.h
 * Type of File    : C Source Code, Header
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Process command line arguments based
 *                 : on a struct which specifies the
 *                 : arguments and responses.
 * (Kernighan & Ritchie, 1988, p. 9, command syntax)
 * (Stefano & Smith, 2009, project file breakdown) */

/* https://www.programiz.com/c-programming/c-structures */

#ifndef __COMMAND_LINE_ARGS_H  /* (cschol, 2008, guard) */
#define __COMMAND_LINE_ARGS_H

#include <stdbool.h>

struct commandLineOption {
    char* shortForm;
    char* longForm;
    char* description;
    char* dataType;
    char* currentValueString;
    bool (*setSetting)(const char*);
    };
/* https://www.geeksforgeeks.org/function-pointer-in-c/ */

int readCommandLineOptions(int commandLineOptionC, 
                        struct commandLineOption options[], 
                           int argc, 
                         char *argv[]);

#endif
/* --------------------- Works Cited -------------------- */
/* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition.." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 * cschol. (2008). "Organization of C files: Answer."
 *      Stackoverflow.  Retrieved from https://stackoverflow
 *      .com/questions/47919/organization-of-c-files on 2022
 *      June 03.
 */
