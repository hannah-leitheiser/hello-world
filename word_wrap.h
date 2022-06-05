/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : gcc hello_world.c -o hello_world
 *  and Run        : ./hello_world
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

#include <stdio.h> /* [Kernighan & Ritchie, 1988, p. 6] */
#include "word_wrap.h"

int getTerminalWidth(void);

const char* wrapText( const char* text, int width=0 );

