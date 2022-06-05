/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : gcc hello_world.c -o hello_world
 *  and Run        : ./hello_world
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

/* https://stackoverflow.com/questions/41841527/why-printf-does-not-output-to-a-file-when-stdout-is-redirected-to-that-file */

#define _GNU_SOURCE
#include <stdio.h> /* [Kernighan & Ritchie, 1988, p. 6] */
#include <stdlib.h> /*https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm*/
#include <stdarg.h> /* https://en.cppreference.com/w/c/variadic/va_list */
#include "gettext.c"
#include "printf.h"

/* https://stackoverflow.com/questions/61306157/unable-to-compile-program-due-to-function-asprintf */

/******************* printf_mine() **************************
 * Perform an explicit flush, see [1].
 * Check for stdio errors. */

/* https://stackoverflow.com/questions/205529/passing-variable-number-of-arguments-around */
int vfprintf_mine(FILE* __stream, const char *__format, va_list argptr) { /* https://github.com/lattera/glibc/blob/master/libio/stdio.h */
    int fprintfReturn = vfprintf(__stream, __format, argptr);
    int flushReturn = 0;
    if(fprintfReturn >= 0) {
        if(fprintfReturn > 0) {
            flushReturn = fflush(__stream);
        }
    }
    else {
        /* Something went very wrong */
        /* https://www.cplusplus.com/reference/cstdio/printf/ */
        /* https://en.cppreference.com/w/c/io/perror */
        char* whatWeTriedtoPrint;
        vasprintf( &whatWeTriedtoPrint, __format, argptr);
        char* whereWeTriedToPrintIt;
        if( __stream == stdout) {
                asprintf( &whereWeTriedToPrintIt, _("the standard output"));
                }
            else if(__stream == stdin) {
                asprintf( &whereWeTriedToPrintIt, _("the standard input"));
                }
                else if (__stream == stderr) {
                asprintf( &whereWeTriedToPrintIt, _("the standard error output"));
                } else {
                 asprintf( &whereWeTriedToPrintIt, _("a file") );
                }
        
        char* errorMessage;
        asprintf(&errorMessage, _("Failure in attempting to print \"%s\" to %s"), whatWeTriedtoPrint, whereWeTriedToPrintIt);
        perror( errorMessage);
        aBadEnd();
    }
    if(flushReturn == EOF )  { /* https://www.tutorialspoint.com/c_standard_library/c_function_fflush.htm */ 
        perror( _("Attempting to flush STDOUT") );
        aBadEnd();
    }
    return fprintfReturn;

}

int printf_mine(const char *__format, ...) {
    va_list argptr;
    va_start(argptr,__format);
    return vfprintf_mine(stdout, __format, argptr);
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
