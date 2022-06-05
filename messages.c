/* Filename        : messages.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : gcc hello_world.c -o hello_world
 *  and Run        : ./hello_world
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

#include "messages.h"

#include <libintl.h> /* [ Fleury, 2016 ] */
#include <locale.h>  /* [ Fleury, 2016 ] */

#define _(STRING) gettext(STRING) /* [ Fleury, 2016, Hello World! Example ] */

/******************* helloMessage  **************************/

const char* helloMessage(void) {
    return _("Hello World!\n");
}

/******************* helpMessage  **************************/

const char* helpMessage(const char* programName) {
    const size_t bufferSize = 500;
    char* returnString = malloc( sizeof(char) * bufferSize);

/* https://stackoverflow.com/questions/3115564/allocating-char-array-using-malloc */

    snprintf(returnString, bufferSize, _("Usage: %s [OPTIONS]\n%s\n%s%s"), 
       programName,
       _("Prints \"Hello World!\".\n"),
       _(" any arguments - Prints this message.\n"),
       _(" no arguments  - Prints Hello World.\n") );

    return returnString;
}
/* https://libslack.org/manpages/snprintf.3.html */
/* [Mutl-line string: Fisher, 2016] */
/* [Help message format: Torbjorn & Stallman, 2022, line 93-125. ] */
/* [Avoid buffer overflow: https://stackoverflow.com/questions/4282281/sprintf-functions-buffer-overflow] */
/* [https://www.cplusplus.com/reference/cstdio/snprintf/] */

/*  Works Cited:
 *  WG14. (2018).  Programming Languages -- C. 9899:202x (E).  ISO/IEC.
 *     Retrieved from https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf
 *     on 2022 June 03.
 *  Kernighan, Brian W. & Ritchie, Dennis M.  (1988).  The C Programming Language.  
 *     Second Edition.  Prentise Hall.  ISBN 0-13-110370-9. 
 *  Fleury, Emmanuel.  2016.  "A Quick Gettext Tutorial."  Retrieved from 
 *      https://www.labri.fr/perso/fleury/posts/programming/a-quick-gettext-tutorial.html
 *      on 2022 June 03.
 *  Thompson, Keith.  2012.  "Should I return EXIT_SUCCESS or 0 
 *     from main()?: Answer."  Stack Overflow.  
 *     Retrieved from 
 *     https://stackoverflow.com/questions/8867871/should-i-return-exit-success-or-0-from-main
 *     on 2022 June 03.
 */
