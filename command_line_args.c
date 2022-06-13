/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : gcc hello_world.c -o hello_world
 *  and Run        : ./hello_world
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

#include <stdbool.h>
#include "command_line_args.h"
#include "debug_log.h"

/* for reference
struct commandLineOption {
    char* shortForm;
    char* longForm;
    char* description;
    char* dataType;
    char* currentValueString;
    };
    */

bool isSubstring( const char* testString, const char* mainString ) {

debugLog(LOG_LEVEL_VERBOSE, "isSubstring():comparing \"%s\" and \"%s\".", testString, mainString);
int i = 0;
while( testString[i] != '\0' && mainString[i] != '\0') {
    if( testString[i] != mainString[i] ) {

        debugLog(LOG_LEVEL_VERBOSE, "isSubstring():no match.");
        return false;
        }
    i++;
    }
/* if we are at the end of the testString; it is fully contained in the mainString. */
if( testString[i] == '\0' ) {
    debugLog(LOG_LEVEL_VERBOSE, "isSubstring():match.");
    return true;
}

debugLog(LOG_LEVEL_VERBOSE, "isSubstring():second string too short, no match.");
return false;

}

int readCommandLineOptions(int commandLineOptionC, struct commandLineOption options[], int argc, char *argv[]) 
{
int currentCommandLineArg = 1; 

while( currentCommandLineArg < argc ) {
        char* currentArg = argv [ currentCommandLineArg ];
        debugLog(LOG_LEVEL_VERBOSE, "readCommandLineOptions():looking at option %s", currentArg);

        bool found = false;
        /* is the first character a '-' ? */
        if( currentArg[0] == '-' ) {
            if( currentArg[1] == '-' ) {
                /* long form */

                debugLog(LOG_LEVEL_VERBOSE, "readCommandLineOptions():detected long form option", currentArg);
                for(int i = 0 ; i < commandLineOptionC ; i++) {
                    if(isSubstring( options[i].longForm, currentArg + 2 )) {
                        // the next arg should be our data
                        if( options[i].dataType[0] == 'b' ) {
                            options[i].currentValueString = "true";
                            options[i].setSetting( options[i].currentValueString );
                            found=true;
                            currentCommandLineArg= currentCommandLineArg + 1;
                            }
                        else {
                            if( currentCommandLineArg+1 < argc) {
                                options[i].currentValueString = argv [ currentCommandLineArg + 1];
                                debugLog(LOG_LEVEL_VERBOSE, "readCommandLineOptions():set %s to %s.", options[i].longForm, options[i].currentValueString);
                                found=true;
                                options[i].setSetting( options[i].currentValueString );
                                currentCommandLineArg= currentCommandLineArg + 2;
                            }
                        }
                    }
                }
            }
        else {

                debugLog(LOG_LEVEL_VERBOSE, "readCommandLineOptions():detected short form option", currentArg);
                for(int i = 0 ; i < commandLineOptionC ; i++) {
                    if(isSubstring( options[i].shortForm, currentArg + 1 )) {

                        if( options[i].dataType[0] == 'b' ) {
                                options[i].currentValueString = "true";
                            found=true;
                            options[i].setSetting( options[i].currentValueString );
                            currentCommandLineArg= currentCommandLineArg + 1;
                            }
                        else {
                        // the next arg should be our data
                        if( currentCommandLineArg+1 < argc) {
                            options[i].currentValueString = argv [ currentCommandLineArg + 1];
                            debugLog(LOG_LEVEL_VERBOSE, "readCommandLineOptions():set %s to %s.", options[i].shortForm, options[i].currentValueString);
                            options[i].setSetting( options[i].currentValueString );
                            found=true;
                            currentCommandLineArg= currentCommandLineArg + 2;
                        }
                        }
                        }
                }
        }
        }
        if(!found) {

            debugLog(LOG_LEVEL_WARNING, "readCommandLineOptions():no match found for %s", currentArg);
            return false;
            }
}

return true;
}



const char* commandLineOptionHelpString( struct commandLineOption* option );



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
/* -------------------- Works Cited -------------------- */
 /* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition.." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 */
