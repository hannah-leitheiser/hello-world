/* Filename        : word_wrap.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Provide function for detecting terminal
 *                 : width and reformating text shortened
 *                 : and wraped to that length.
 * (Kernighan & Ritchie, 1988, p. 9: comment syntax) */

#define _GNU_SOURCE
#include <stdio.h> /* [(Kernighan & Ritchie, 1988, p. 6) */
#include <string.h>
#include <stdlib.h>

#include <sys/ioctl.h>  /* ( Regents, 1991 ) */
#include <unistd.h>

/* src/ headers */

#include "word_wrap.h"
#include "debug_log.h"

/* ------------ getTerminalWidth() ---------------------- */

int getTerminalWidth(void) { 

    struct winsize w;

    /* ( T, 2009 ) */
    if ( ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) ) {
        /* ( Regents, 1991 ) */
        return w.ws_col;
    }
    return NOWRAP;
}

/* -------------------- wrapText() ---------------------- */

char* wrapText( const char* text, int width, 
          const char* initialIndent, 
          const char* subsequentIndent ) {

int inputTextIndex = 0;
char* outputText = "";
bool firstLine = true;

int inputTextLength = strlen(text);
    /* ( Parewa Labs, n.d., C strlen() ) */

if(width == NOWRAP) {
    /* we still need to add the indent */

    asprintf( &outputText, "%s", initialIndent); 
    for( ; inputTextIndex < inputTextLength; inputTextIndex++) {

        asprintf(&outputText, "%s%c", outputText, text[inputTextIndex]);
        if( text[inputTextIndex] == '\n' && inputTextIndex < inputTextLength-1 ) {
        asprintf(&outputText, "%s%s", outputText, subsequentIndent);
        }

    }
    return outputText;
}


if(width == AUTODETECT) {
    width = getTerminalWidth();
    if(width == AUTODETECT) {
        width = DEFAULT_WIDTH;
        }
}

if(width < 1) {
    /* the function will hang if the width is 0 or less */
    width = DEFAULT_WIDTH;
    }

/* if the indent is longer than the target width, we are
   going to make the indent nothing ("") */

if( strlen(initialIndent) + 1 > width ) {
    initialIndent = "";
}

if( strlen(subsequentIndent) + 1 > width ) {
    subsequentIndent = "";
}

int textColumns;

//debugLog( LOG_LEVEL_VERBOSE, "wrapText():columns:%d, textColumns:%d, indent: %d", columns, textColumns, indent );

while( inputTextIndex < inputTextLength) {
    char* indent;
    if(firstLine) {
        indent = initialIndent;
        firstLine = false;
    }
    else {
        indent = subsequentIndent;
    }

    textColumns = width - strlen(indent);

    char* line = malloc( sizeof(char) * (textColumns+1) );


    int breakPoint;

    /* trim out spaces, but only if textColumns is greater than 1 */
    while( text[inputTextIndex] == ' ') {
        if( textColumns < 5 ) {
            /* if we are in 1 to 4 columns, make spaces new lines. */
            asprintf( &outputText, "%s%s\n", outputText, indent); 
            }
        inputTextIndex++;
    }

    if( inputTextIndex + textColumns < inputTextLength ) {

        debugLog( LOG_LEVEL_VERBOSE, "wrapText():line has to be split" );
        /* we have to find a breakpoint */
        breakPoint = textColumns-1;
        while( (text[inputTextIndex + breakPoint] != ' ' && text[inputTextIndex + breakPoint] != '\n')  && (breakPoint >= 0) ) {
            breakPoint--;
            }
        if(breakPoint == -1) {

            debugLog( LOG_LEVEL_VERBOSE, "wrapText():no good split found." );
            breakPoint = textColumns;
        }
    }
    else {
        breakPoint = inputTextLength - inputTextIndex;

        
        debugLog( LOG_LEVEL_VERBOSE, "wrapText():last line, breakpoint=%d", breakPoint );
    }
        int i;
        for(i = 0 ; i < breakPoint && text[inputTextIndex] != '\n' ; i++) {
            debugLog( LOG_LEVEL_VERBOSE, "wrapText():char to line:%c, i=%d", text[inputTextIndex], i );
            line[i] = text[inputTextIndex];
            inputTextIndex++;
        }

        debugLog( LOG_LEVEL_VERBOSE, "wrapText():termination i=%d", i );
        if( line[i-1] == '\n') {
            line[i-1] = '\0'; /* it will add a return, so don't double. */
        }
        else {
            line[i] = '\0';
        }
        
        asprintf( &outputText, "%s%s%s\n", outputText, indent, line);
        /* alternately, if the new line is next, go past that */
        if( text[ inputTextIndex ] == '\n') {
            inputTextIndex++; } 
    free ( line);
    }

/* was there no trailing '\n' in the input? */
if( text[ inputTextLength-1 ] != '\n' ) {
    /* then take it out of the output */
    outputText[ strlen(outputText) - 1 ] = '\0';
    }


return outputText;
}

/* --------------------- Works Cited -------------------- */
/* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 * Parewa Labs. (n.d.). "C strlen()." Parewa Labs Pvt. Ltd..
 *      Retrieved from
 *      https://www.programiz.com/c-programming/library-
 *      function/string.h/strlen on 2022 December 28.
 * Regents of the University of California. (1991).
 *      "ioctl(2) — Linux manual page." GNU Linux.
 *      Retrieved from https://man7.org/linux/man-
 *      pages/man2/ioctl.2.html on 2022 December 28.
 * T, John. (2009). "Getting terminal width in C?: Answer."
 *      Stackoverflow.  Retrieved from
 *      https://stackoverflow.com/questions/1022957/getting-
 *      terminal-width-in-c on 2022 December 28.
 */
