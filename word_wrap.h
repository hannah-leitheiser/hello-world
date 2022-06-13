/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : gcc hello_world.c -o hello_world
 *  and Run        : ./hello_world
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

#include <stdbool.h>

#ifndef __WORD_WRAP_H /* [guard modeled on cschol, 2008] */
#define __WORD_WRAP_H

#define AUTODETECT      0
#define NOWRAP         -1
#define DEFAULT_WIDTH  80

int getTerminalWidth(void);

/* https://stackoverflow.com/questions/14526153/multiple-definition-of-a-global-variable */

/* https://stackoverflow.com/questions/2988038/default-values-on-arguments-in-c-functions-and-function-overloading-in-c */

/* https://stackoverflow.com/questions/479207/how-to-achieve-function-overloading-in-c */

char* wrapText( const char* text, int width,                 
          const char* initialIndent,                         
          const char* subsequentIndent );
   /* arguments modeled after 
           ( Python Software Foundation, 2022 ) */

#endif

/* -------------------- Works Cited -------------------- */
 /* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition.." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 */
