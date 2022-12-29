/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : gcc hello_world.c -o hello_world
 *  and Run        : ./hello_world
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

#define _GNU_SOURCE /* ( shadowchaser, 2020 ) */
#include <stdio.h> /* [Kernighan & Ritchie, 1988, p. 6] */
#include <stdlib.h> 
#include <stdarg.h> /* ( cppreference.com, 2020 ) */
#include "gettext.h"
#include "printf.h"

char* nameStream( FILE* __stream) {
        if(__stream == NULL) {
            return "NULL";
        }
        if( __stream == stdout) {
                return "the standard output";
                }
        if(__stream == stdin) {
                return "the standard input";
                }
        return "a file";
}

/******************* printf_mine() **************************
 * Perform an explicit flush.
 * Check for stdio errors. */

int vfprintf_mine(FILE* __stream, const char *__format, 
                                          va_list argptr) { 
                      /* ( Meyers, et. al, 2018 ) */
    int fprintfReturn = vfprintf(__stream, __format, argptr);
    int flushReturn = 0;
    if(fprintfReturn >= 0) {
        if(fprintfReturn > 0) {
            /* ( sureshkumar, 2017 ) */
            /* Try to make printing a bit more robust. */
            flushReturn = fflush(__stream);
        }
    }
    else {
        /* Something went very wrong */
        /* ( cplusplus.com, n. d.) */
        char* whatWeTriedtoPrint;
        vasprintf( &whatWeTriedtoPrint, __format, argptr);
        char* whereWeTriedToPrintIt = nameStream(__stream);
        
        char* errorMessage;
        asprintf(&errorMessage, 
           _("Failure in attempting to print \"%s\" to %s"), 
               whatWeTriedtoPrint, whereWeTriedToPrintIt);
        /* ( cppreference.com, 2021 ) */
        perror( errorMessage);
        return -1;
    }
    /* ( Tutorialspoint, 2022 ) */
    if(flushReturn == EOF )  {  
        perror( _("Attempting to flush STDOUT") );
        return -1;
    }
    return fprintfReturn;

}

int printf_mine(const char *__format, ...) {
    /* ( smacL, 2008 ) */
    va_list argptr;
    va_start(argptr,__format);
    return vfprintf_mine(stdout, __format, argptr);
}

/* --------------------- Works Cited -------------------- */
/* 
 * Joseph Meyers, Ulrich Drepper, Zack Weinberg, et. al..
 *      (2018). "studio.h." glibc.  Retrieved from https://g
 *      ithub.com/lattera/glibc/blob/master/libio/stdio.h on
 *      2022 June 09.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 * Tutorialspoint. (2022). "C library function - fflush()."
 *      Tutorialspoint.  Retrieved from https://www.tutorial
 *      spoint.com/c_standard_library/c_function_fflush.htm
 *      on 2022 June 09.
 * cplusplus.com. (n. d.). "printf." cplusplus.com.
 *      Retrieved from
 *      https://cplusplus.com/reference/cstdio/printf/ on
 *      2022 June 09.
 * cppreference.com. (2020). "va_list." cppreference.com.
 *      Retrieved from
 *      https://en.cppreference.com/w/c/variadic/va_list on
 *      2022 July 16.
 * cppreference.com. (2021). "perror." cppreference.com.
 *      Retrieved from
 *      https://en.cppreference.com/w/c/io/perror on 2022
 *      December 28.
 * shadowchaser. (2020). "unable to compile program due to
 *      function asprintf: Answer." Stackoverflow.
 *      Retrieved from
 *      https://stackoverflow.com/questions/61306157/unable-
 *      to-compile-program-due-to-function-asprintf on 2022
 *      December 28.
 * smacL. (2020). "Passing variable number of arguments
 *      around: Answer." Stackoverflow.  Retrieved from
 *      https://stackoverflow.com/questions/205529/passing-
 *      variable-number-of-arguments-around on 2022 December
 *      28.
 * sureshkumar. (2017). "Why printf() does not output to a
 *      file, when stdout is redirected to that file?:
 *      Answer." Stackoverflow.  Retrieved from
 *      https://stackoverflow.com/questions/41841527/why-
 *      printf-does-not-output-to-a-file-when-stdout-is-
 *      redirected-to-that-file on 2022 December 28.
 */
