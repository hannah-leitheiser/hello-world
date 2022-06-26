/* Filename        : hello_world.h
 * Type of File    : C Source Code, Header
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * File Summary    : Header file.
 * (C Comment Syntax: Kernighan & Ritchie, 1988, p. 9)
 * (File Use: Borini & Smith, 2009 ) */

#ifndef __HELLO_WORLD_H /*(guard modeled on cschol, 2008)*/    
#define __HELLO_WORLD_H 

#define DEBUG_LOG                                                
#define CONFIGURATION_FILE "hello_world.conf"
#define PACKAGE "hello_world"
#define LOCALE_DIR "po/"

struct helloWorldSettings {
    int textWidth;
    const char* specifiedLanguage;
};

int main(int argc, char *argv[]); 
      /* (from WG14, 2018, p. 11) */

void aBadEnd( void );

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
 * WG14. (2018). "Programming Languages -- C. 9899:202x
 *      (E)." ISO/IEC.  Retrieved from https://www.open-
 *      std.org/jtc1/sc22/wg14/www/docs/n2310.pdf on 2022
 *      June 03.
 * cschol. (2008). "Organization of C files: Answer."
 *      Stackoverflow.  Retrieved from https://stackoverflow
 *      .com/questions/47919/organization-of-c-files on 2022
 *      June 03.
 */
