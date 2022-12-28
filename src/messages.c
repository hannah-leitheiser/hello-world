/* Filename        : messages.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Generates text associated with 
                     message to greet the world and 
                     help message.
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

const char* helloMessage(int width) {
        return wrapText( 
               _("Hello, world!"), 
		width, "", "" );
}


/* ------------- versionMessage() ----------------------- */

/* Helper function prototypes: */

const char* getBanner();

const char* versionMessage( int width ) {
    return wrapText(
            _( getBanner() ),
            width, "", "");
}

const char* defaultBanner = 
   #include "banner.txt"
   ;

const char* getBanner() {
   return defaultBanner;
}

/* ---------------- helpMessage() ----------------------- */

/* Helper function prototypes: */

const char* getBanner();
const char* getDescription();
const char* generateCommandLineOptionString(
        const char* shortForm,
        const char* longForm,
        const char* description,
        int width );
const char* helpMessageAsprintfFail();
const char* generateCommandLineOptionStringAsprintfFail();

/* function */

const char* helpMessage(    const char* programName, 
                                    int commandLineOptionC, 
               struct commandLineOption options[], 
                                    int width) {
    char* returnString;
    void* toFree;
    int   asprintfReturn;

    /* ( Stackoverflow, 2022: reviewed as deciding on how
         to generate strings ) */

    asprintfReturn = asprintf(&returnString, 
             "%sUsage: %s [OPTIONS]\n\n", 
                 getBanner(), 
                 programName);

    /* (Brouwer, 2001: return value) */
    if(asprintfReturn < 0) {
         return helpMessageAsprintfFail();
    }

    toFree = (void*)returnString;
    returnString = wrapText(returnString, width,"","");
    free( toFree );

    
    const char* description = 
              wrapText( getDescription(), width, "", "");

    toFree = (void*)returnString;
    asprintfReturn = asprintf(&returnString, 
             "%s%s\n", 
                 returnString,
                 description );

    /* (Brouwer, 2001: return value) */
    if(asprintfReturn < 0) {
         return helpMessageAsprintfFail();
    }
    free( toFree );
    free( (void*) description );

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

    for(int i = 0 ; i < commandLineOptionC ; i++) {
        const char* optionString = 
           generateCommandLineOptionString(
               options[i].shortForm,
               options[i].longForm,
               options[i].description,
               width);
        toFree = (void*)returnString;
        asprintfReturn = asprintf(&returnString, 
                      "%s%s", returnString, optionString);
    
        /* (Brouwer, 2001: return value) */
        if(asprintfReturn < 0) {
             return helpMessageAsprintfFail();
        }
        free(toFree);

    }

    const char* optionString = 
           generateCommandLineOptionString(
               "h",
               "help",
               "Display this message.",
               width);
    toFree = (void*)returnString;
    asprintfReturn = asprintf(&returnString, 
                  "%s%s", returnString, optionString);

    /* (Brouwer, 2001: return value) */
    if(asprintfReturn < 0) {
         return helpMessageAsprintfFail();
    }
    free(toFree);

    return returnString;
}

const char* defaultDescription = 
   #include "description.txt"
   ;

const char* getDescription() {
   return defaultDescription;
}

const char* generateCommandLineOptionString(
        const char* shortForm,
        const char* longForm,
        const char* description,
        int width ) {
    char* returnString;
    char* firstPart;
    int   asprintfReturn;
    void* toFree;
    
    asprintfReturn = asprintf(&firstPart, " -%s, --%s\n", 
                    shortForm, longForm);

    /* (Brouwer, 2001: return value) */
    if(asprintfReturn < 0) {
         return 
             generateCommandLineOptionStringAsprintfFail();
    }

    char* descp;
    descp = wrapText( description, width, "     ", "     ");

    toFree = (void*)firstPart;
    firstPart = wrapText(firstPart,width,"","");
    free(toFree);
    asprintfReturn = asprintf(&returnString, 
                       "%s%s\n", firstPart, descp);

    free(firstPart);
    free(descp);

    /* (Brouwer, 2001: return value) */
    if(asprintfReturn < 0) {
         return 
             generateCommandLineOptionStringAsprintfFail();
    }

    return (const char*) returnString;
    }


const char* helpMessageAsprintfFail() {
    debugLog(LOG_LEVEL_WARNING,
             "helpMessageAsprintfFail:Unable to produce "
             "help message due to asprintf failure.");
                   /* ( Fisher, 2016: multi-line string ) */ 
    return "";
}


const char* generateCommandLineOptionStringAsprintfFail() {
    debugLog(LOG_LEVEL_WARNING,
             "generateCommandLineOptionStringAsprintfFail:"
             "Unable to produce "
             "help message due to asprintf failure.");  
    return "";
}

/* [Help message format: Torbjorn & Stallman, 2022, line 93-125. ] */

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
 * Stackoverflow. (2022). "sprintf function's buffer
 *      overflow?." Stackoverflow.  Retrieved from
 *      https://stackoverflow.com/questions/4282281/sprintf-
 *      functions-buffer-overflow on 2022 June 18.
 */
