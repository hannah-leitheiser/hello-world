/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : gcc hello_world.c -o hello_world
 *  and Run        : ./hello_world
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

#define _GNU_SOURCE

#include <stdio.h> /* [Kernighan & Ritchie, 1988, p. 6] */
#include <string.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "word_wrap.h"
#include "debug_log.h"


int wrapColumns = AUTODETECT;
bool noWrap = false;

int setWrapWidth(int width) {
    wrapColumns = width;
}
int setNoWrap(bool value) {
    noWrap = value;
}



int getTerminalWidth(void) { 
/* https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c */
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return w.ws_col;
}

const char* wrapText( const char* text, int indent ) {


int inputTextIndex = 0;
char* outputText = "";

/*https://www.programiz.com/c-programming/library-function/string.h/strlen*/
int inputTextLength = strlen(text);

if(noWrap) {
    /* we still need to add the indent */

    asprintf( &outputText, "%s%*s", outputText, indent, ""); 
    for( ; inputTextIndex < inputTextLength; inputTextIndex++) {

        asprintf(&outputText, "%s%c", outputText, text[inputTextIndex]);
        if( text[inputTextIndex] == '\n' && inputTextIndex < inputTextLength-1 ) {
        asprintf(&outputText, "%s%*s", outputText, indent, "");
        }

    }
    return outputText;
}


int columns = wrapColumns;

if(columns == AUTODETECT) {
    columns = getTerminalWidth();
    if(columns <= 0) {
        columns = 80;
        }
}
int textColumns = columns - indent;

char* line = malloc( sizeof(char) * (textColumns+1) );
debugLog( LOG_LEVEL_VERBOSE, "wrapText():columns:%d, textColumns:%d, indent: %d", columns, textColumns, indent );



while( inputTextIndex < inputTextLength) {
    int breakPoint;

    /* trim out spaces, but only if textColumns is greater than 1 */
    while( text[inputTextIndex] == ' ') {
        if( textColumns < 3 ) {
            /* if we are in 1 or 2 columns, make spaces new lines. */
            asprintf( &outputText, "%s%*s%s\n", outputText, indent, "", ""); 
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
        
        asprintf( &outputText, "%s%*s%s\n", outputText, indent, "", line);
        /* alternately, if the new line is next, go past that */
        if( text[ inputTextIndex ] == '\n') {
            inputTextIndex++; } 

    }

free( line );
return outputText;
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
 /* Works Cited */
 /* 
Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C Programming Language, Second Edition.." Prentise Hall..  ISBN 0-13-110370-9.
 */
