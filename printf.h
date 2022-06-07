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

#define printf printf_mine
char* nameStream( FILE* __stream);
int printf_mine(const char *__format, ...);

/* Works Cited:
 *  Borini, Stefano & Smith, Jed.  2009.  "What do .c and .h file extensions mean to C?"  Stack Overflow.  
 *     Retrieved from https://stackoverflow.com/questions/1695224/what-do-c-and-h-file-extensions-mean-to-c on 
 *  Brian W. Kernighan & Dennis M. Ritchie.  1988.  The C Programming Language.  
 *      Second Edition.  Prentise Hall.  ISBN 0-13-110370-9. 
 *  Fisher, Jim. (2016). How do I write a multi-line string literal in C?.  
 *      Retrieved from https://jameshfisher.com/2016/11/30/c-multiline-literal/ on 2022 June 03.
 *  Granlund, Torbjorn & Stallman, Richard M.  2022.  cat.c.  GNU core utilities.  
 *      Retrieved from https://github.com/coreutils/coreutils/blob/master/src/cat.c on 2022 June 03.
 *  WG14. (2018).  Programming Languages -- C. 9899:202x (E).  ISO/IEC.
 *      Retrieved from https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf
 *      on 2022 June 03.
 *
 */
