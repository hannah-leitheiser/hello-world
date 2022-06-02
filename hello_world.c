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

/******************* int main() **************************
 * Outpus "Hello World!" to stdout -- likely as text to 
 * the terminal.
 * [program similar to Kernighan & Ritchie, 1998, p. 6] */

int main() { /* todo: reference for use of int */
  printf("Hello World!");
  return 0; /*  todo: reference for happy exit */
}

/*  Works Cited:
 *  Brian W. Kernighan & Dennis M. Ritchie.  1988.  The C Programming Language.  
 *     Second Edition.  Prentise Hall.  ISBN 0-13-110370-9. 
 */
