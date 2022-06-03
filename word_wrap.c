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
#include "hello_world.h"

/******************* int main() **************************
 * Outpus "Hello World!" to stdout -- likely as text to 
 * the terminal.
 * [function similar to Kernighan & Ritchie, 1998, p. 6] */

int main(int argc, char *argv[]) { /* [from WG14, 2018, p. 11] */
  if(argc == 0) {
    printf(Hello_Message); /* if no command-line argument is */
                           /* supplied. */
  }
  else {
    printf(Help_Message);  /* if any command-line argument is */
                           /* supplied.  */
  }
  /* [if statement modeled after Kernighan & Richie, 1998, p. 20
          or similar ] */
  return EXIT_SUCCESS;  /* [program exit: WG14, 2018, p. 11,
                            EXIT_SUCCESS: Thompson, 2012 ] */
}

/*  Works Cited:
 *  WG14. (2018).  Programming Languages -- C. 9899:202x (E).  ISO/IEC.
 *     Retrieved from https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf
 *     on 2022 June 03.
 *  Kernighan, Brian W. & Ritchie, Dennis M.  (1988).  The C Programming Language.  
 *     Second Edition.  Prentise Hall.  ISBN 0-13-110370-9. 
 *  Thompson, Keith.  2012.  "Should I return EXIT_SUCCESS or 0 
 *     from main()?: Answer."  Stack Overflow.  
 *     Retrieved from 
 *     https://stackoverflow.com/questions/8867871/should-i-return-exit-success-or-0-from-main
 *     on 2022 June 03.
 */
