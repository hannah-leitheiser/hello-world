/* Filename        : command_line_args.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Process command line arguments based
 *                 : on a struct which specifies the
 *                 : arguments and responses.
 * (Comment Syntax: Kernighan & Ritchie, 1988, p. 9) */

#include <stdbool.h>
#include "command_line_args.h"
#include "debug_log.h"

/* ----------------- isSubstring ------------------------ */
/* this function tests whether testString is fully contained
 * in the beginning of mainString.  This is in case we
 * want to test for command line argumentments in the form
 * --width=10 at some future time.                        */

bool isSubstring( const char* testString, 
                  const char* mainString ) {
    debugLog(LOG_LEVEL_VERBOSE, 
             "isSubstring():comparing \"%s\" and \"%s\".", 
                       testString, mainString);
    int i = 0;
    while( testString[i] != '\0' && mainString[i] != '\0') {
        if( testString[i] != mainString[i] ) {

            debugLog(LOG_LEVEL_VERBOSE, 
                         "isSubstring():no match.");
            return false;
            }
        i++;
        }
    /* if we are at the end of the testString; */
    /* it is fully contained in the mainString. */
    if( testString[i] == '\0' ) {
        debugLog(LOG_LEVEL_VERBOSE, "isSubstring():match.");
        return true;
    }

    debugLog(LOG_LEVEL_VERBOSE, 
            "isSubstring():second string too short, "
            "no match.");
    return false;
}

/* for reference, defined in command_line_args.h:

struct commandLineOption {                                   
    char* shortForm;                                         
    char* longForm;                                          
    char* description;                                       
    char* dataType;                                          
    char* currentValueString;                                
    bool (*setSetting)(const char*);                         
    };

*/

/* -----------readCommandLineOptions -------------------- */
/* compare the command-line options supplied to main() 
 * to the command line options array.  In the event of a 
 * match for either the short (eg. -w) or long 
 * (eg. --width) form, set the currentValueString and 
 * execute setSettings -- a pointer to a function that's
 * suppose to realize the setting in the program generally.
 */

int readCommandLineOptions(int commandLineOptionC, 
                        struct commandLineOption options[], 
                           int argc, 
                         char *argv[]) {
    int currentCommandLineArg = 1; 

    while( currentCommandLineArg < argc ) {
            char* currentArg = 
                        argv [ currentCommandLineArg ];
            debugLog(LOG_LEVEL_VERBOSE, 
                      "readCommandLineOptions():"
                      "looking at option %s", currentArg);

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

/* --------------------- Works Cited -------------------- */
/* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition.." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 */
