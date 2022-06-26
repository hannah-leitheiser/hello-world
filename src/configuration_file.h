/* Filename        : hello_world.h
 * Type of File    : C Source Code, Header
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * (Kernighan & Ritchie, 1988, p. 9: comment syntax]
 * (Borini & Smith, 2009, project file breakdown) */

#ifndef __CONFIGURATION_FILE_H 
#define __CONFIGURATION_FILE_H
/* (cschol, 2008: header guard) */

#include <stdbool.h>
#include "command_line_args.h"

bool readConfigurationFile(FILE* file, 
  int commandLineOptionC, 
        struct commandLineOption options[]);

#endif
/* --------------------- Works Cited -------------------- */
/* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 * Smith, Jed & Borini, Stefano. (2009). "What do .c and .h
 *      file extensions mean to C?, Answer." Stackoverflow.
 *      Retrieved from
 *      https://stackoverflow.com/questions/1695224/what-do-
 *      c-and-h-file-extensions-mean-to-c on 2022 June 03.
 * cschol. (2008). "Organization of C files: Answer."
 *      Stackoverflow.  Retrieved from https://stackoverflow
 *      .com/questions/47919/organization-of-c-files on 2022
 *      June 03.
 */
