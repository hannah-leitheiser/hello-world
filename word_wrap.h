/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : gcc hello_world.c -o hello_world
 *  and Run        : ./hello_world
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

#define AUTODETECT 0

int getTerminalWidth(void);

/* https://stackoverflow.com/questions/2988038/default-values-on-arguments-in-c-functions-and-function-overloading-in-c */

const char* wrapText( const char* text, int columns, int indent);
