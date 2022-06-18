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

/* [Mutl-line string: Fisher, 2016] */
/* [Help message format: Torbjorn & Stallman, 2022, line 93-125. ] */

#ifndef __HELLO_WORLD_H /* [guard modeled on cschol, 2008] */    
#define __HELLO_WORLD_H 

#define DEBUG                                                
#define PACKAGE "hello_world"
#define LOCALEDIR "po/"
#define CONFIGURATION_FILE "hello_world.conf"  


struct helloWorldSettings {
    int textWidth;
    const char* specifiedLanguage;
};

int main(int argc, char *argv[]); /* [from WG14, 2018, p. 11] */

void aBadEnd( void );

#endif

/* Works Cited:
 *  Borini, Stefano & Smith, Jed.  2009.  "What do .c and .h file extensions mean to C?"  Stack Overflow.  
 *     Retrieved from https://stackoverflow.com/questions/1695224/what-do-c-and-h-file-extensions-mean-to-c on 
 *  Granlund, Torbjorn & Stallman, Richard M.  2022.  cat.c.  GNU core utilities.  
 *      Retrieved from https://github.com/coreutils/coreutils/blob/master/src/cat.c on 2022 June 03.
 *
 */
/* -------------------- Works Cited -------------------- */
/* 
 * Fisher, James. (2016). "How do I write a multi-line
 *      string literal in C?." Website.  Retrieved from
 *      https://jameshfisher.com/2016/11/30/c-multiline-
 *      literal/ on 2022 June 14.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition.." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 * WG14. (2018). "Programming Languages -- C. 9899:202x
 *      (E)." ISO/IEC.  Retrieved from https://www.open-
 *      std.org/jtc1/sc22/wg14/www/docs/n2310.pdf on 2022
 *      June 03.
 */