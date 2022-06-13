/* Filename        : messages.c
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
#include <stdlib.h>
#include <libintl.h> /* [ Fleury, 2016 ] */
#include <locale.h>  /* [ Fleury, 2016 ] */

#include "gettext.h"
#include "command_line_args.h"
#include "word_wrap.h"

#include "messages.h"

/******************* helloMessage  **************************/

const char* helloMessage(void) {
    return _("Hello World!\n");
}

const char* defaultBanner = "Hello World!\n";

const char* getBanner() {
    /* https://www.tutorialkart.com/c-programming/c-read-text-file/ */
    FILE    *bannerFile;
    char    *text;
    long    numbytes;

    bannerFile = fopen("banner.txt", "r");
    if(bannerFile == NULL) {
        return defaultBanner;
    }

    fseek(bannerFile, 0L, SEEK_END);
    numbytes = ftell(bannerFile);
    fseek(bannerFile, 0L, SEEK_SET);

    text = (char*)calloc(numbytes, sizeof(char));
    if(text == NULL)
        return defaultBanner;

    fread(text, sizeof(char), numbytes, bannerFile);
    fclose(bannerFile);

    return text;

}

/******************* helpMessage  **************************/

const char* helpMessage(const char* programName, int commandLineOptionC, struct commandLineOption options[], int width) {
    char* returnString;

/* https://stackoverflow.com/questions/3115564/allocating-char-array-using-malloc */

   asprintf(&returnString, "%sUsage: %s [OPTIONS]\n\n", 
       wrapText( getBanner(), width, "", ""), programName); 

/* struct commandLineOption {
    char* shortForm;
    char* longForm;
    char* description;
    char* dataType;
    char* currentValueString;
    }; */

returnString = wrapText(returnString, width,"","");

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
/* -------------------- Works Cited -------------------- */
 /* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition.." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 */
