/* Filename        : messages.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * (Kernighan & Ritchie, 1988, p. 9: Comment Syntax ) */

#define _GNU_SOURCE /* (Brouwer, 2001, Synopsis )         */
#include <stdio.h>  /* (Kernighan & Ritchie, 1988, p. 6)  */
#include <stdlib.h> /* (Koenig & Kerrisk, 2018, Synopsis) */

#include "gettext.h"
#include "command_line_args.h"
#include "word_wrap.h"
#include "debug_log.h"

#include "messages.h"

/* ---------------- helloMessage() ---------------------- */

const char* helloMessage(void) {
    return _("Hello World!\n");
}

/* ---------------- helpMessage() ----------------------- */

/* Helper function prototypes: */
const char* helpMessageAsprintfFail();
const char* getBanner();

const char* helpMessage(    const char* programName, 
                                    int commandLineOptionC, 
               struct commandLineOption options[], 
                                    int width) {
    char* returnString;
    void* toFree;
    int   asprintfReturn;

    asprintfReturn = asprintf(&returnString, 
             "%sUsage: %s [OPTIONS]\n\n", 
                 getBanner(), 
                 programName);

    /* (Brouwer, 2001: return value) */
    if(asprintfReturn < 0) {
         return helpMessageAsprintfFail();
    }

    /* for reference:
    struct commandLineOption {
        const char* shortForm;
        const char* longForm;
        const char* description;
        const char* dataType;
        const char* currentValueString;
        bool (*setSetting)(const char*);
        };
        */

    toFree = (void*)returnString;
    returnString = wrapText(returnString, width,"","");
    free( toFree );

for(int i = 0 ; i < commandLineOptionC ; i++) {
    char* firstPart;
    asprintf(&firstPart, " -%s --%s\n", options[i].shortForm, options[i].longForm);
    char* descp;
    descp = wrapText( options[i].description, width, "     ", "     ");
    firstPart = wrapText(firstPart,width,"","");
    asprintf(&returnString, "%s%s%s\n", returnString, firstPart, descp);
}


char* firstPart;
asprintf(&firstPart, " -%s --%s\n", "h", "help");
char* descp;
descp = wrapText( "Display this message.", width, "     ", "     ");
firstPart = wrapText(firstPart,width,"","");
asprintf(&returnString, "%s%s%s\n", returnString, firstPart, descp);


    return returnString;
}

const char* defaultBanner = 
   #include "banner.txt"
   ;

const char* getBanner() {
   return defaultBanner;
}

const char* helpMessageAsprintfFail() {
    debugLog(LOG_LEVEL_WARNING,
             "helpMessageAsprintfFail:Unable to produce "
             "help message due to asprintf failure.");  
    return "";
}

/* https://libslack.org/manpages/snprintf.3.html */
/* [Mutl-line string: Fisher, 2016] */
/* [Help message format: Torbjorn & Stallman, 2022, line 93-125. ] */
/* [Avoid buffer overflow: https://stackoverflow.com/questions/4282281/sprintf-functions-buffer-overflow] */
/* [https://www.cplusplus.com/reference/cstdio/snprintf/] */

/* --------------------- Works Cited -------------------- */
/* 
 * Brouwer, Andries. (2001). "asprintf(3) — Linux manual
 *      page." GNU Linux.  Retrieved from
 *      https://man7.org/linux/man-
 *      pages/man3/asprintf.3.html on 2022 June 25.
 * Fisher, James. (2016). "How do I write a multi-line
 *      string literal in C?." Website.  Retrieved from
 *      https://jameshfisher.com/2016/11/30/c-multiline-
 *      literal/ on 2022 June 14.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 * Koenig, Thomas & Kerrisk, Michael. (2018). "malloc(3) —
 *      Linux manual page." GNU Linux.  Retrieved from
 *      https://man7.org/linux/man-pages/man3/malloc.3.html
 *      on 2022 July 14.
 */
