/* Filename        : command_line_args.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Process command line arguments based
 *                 : on a struct which specifies the
 *                 : arguments and responses.
 * (Comment Syntax: Kernighan & Ritchie, 1988, p. 9) */


#define _GNU_SOURCE /* (Brouwer, 2001, Synopsis )         */ 
#include <stdio.h>  /* (Kernighan & Ritchie, 1988, p. 6)  */ 
#include <stdbool.h> /*(IEEE, Inc & The Open Group, 2018) */
#include <string.h>
#include <stdlib.h>
 #include <getopt.h>
#include <unistd.h>



#include "debug_log.h"
#include "error.h"

#include "command_line_args.h"

enum optionType { longForm, shortForm };
/* ( GeeksforGeeks et. al., 2022: enum syntax ) */

bool readOption( const char* option,
             enum optionType type,
                 const char* predicate,
                                /* 2nd "return value" */
                        bool* predicateUsed, 
                         int commandLineOptionC,           
                      struct commandLineOption options[]);

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

/* -----------readCommandLineOptions -------------------- */
/* compare the command-line options supplied to main() 
 * to the command line options array.  In the event of a 
 * match for either the short (eg. -w) or long 
 * (eg. --width) form, set the currentValueString and 
 * execute setSettings -- a pointer to a function that's
 * suppose to realize the setting in the program generally.
 * return values:
 *     true: all command line options successfully 
 *             processed.
 *     false: at least one option not recgonized.
 */

/* for reference, defined in command_line_args.h:

struct commandLineOption {                                   
    const char* shortForm;                                   
    const char* longForm;                                    
    const char* description;                                 
    bool        takesArgument;                               
    bool        requiresArgument;                            
    bool        endsProgram;                                 
    const char* argument;                          
    bool (*setSetting)(const char*);                         
    };                                                       

*/

bool readCommandLineOptions(int commandLineOptionC, 
                        struct commandLineOption options[], 
                           int argc, 
                         char *argv[]) {
    
/* (Koenig & Kerrisk, 2008) */
/*  struct option {
               const char *name;
               int         has_arg;
               int        *flag;
               int         val;
           }; */

struct option* getOptStruct = 
      malloc( sizeof( struct option) * (commandLineOptionC + 1 ) );
char* shortOptionString = ":";

for(int i = 0 ; i < commandLineOptionC ; i++) {
    getOptStruct[i].name = options[i].longForm;
    if( options[i].takesArgument &&
         options[i].requiresArgument) {
        getOptStruct[i].has_arg = required_argument;
    }

    if( options[i].takesArgument &&
         !options[i].requiresArgument) {
        getOptStruct[i].has_arg = optional_argument;
    }

    if( !options[i].takesArgument &&
         !options[i].requiresArgument) {
        getOptStruct[i].has_arg = no_argument;
    }
    getOptStruct[i].flag=0;
    getOptStruct[i].val=0;
    for(int ii = 0 ; options[i].shortForm[ii] != '\0' ;
              ii++) {

        
        asprintf(&shortOptionString, "%s%c", shortOptionString, 
          options[i].shortForm[ii]);
        
        if( options[i].takesArgument) {

        asprintf(&shortOptionString, "%s%c", shortOptionString, ':');
        
    
            if( !options[i].requiresArgument) {

            asprintf(&shortOptionString, "%s%c", shortOptionString, ':');
            }
        }

    }
}
getOptStruct[ commandLineOptionC ] = (struct option){
    0, 0, 0, 0 };
    

int getoptReturn;
int option_index;
while( (getoptReturn = getopt_long(argc, argv, shortOptionString,
                        getOptStruct, &option_index))
                        != -1) {
    if(optopt != NULL) {
    printf("optopt: %c\n", optopt);
    }
    
    if(getoptReturn == 0) {
    }
    else {
        for(int i = 0 ; i < commandLineOptionC ; i++) {
        
            for(int ii = 0 ; options[i].shortForm[ii] != '\0' ;
              ii++) {
                if(getoptReturn == options[i].shortForm[ii]) {
                    option_index = i;
                }
            }

        }

    }
    options[option_index].argument = optarg;

    int setSettingReturn = 
                        options[option_index].setSetting( 
                         options[option_index].argument );
    printf("%s\n", options[option_index].longForm );
    

}



/*

    int currentCommandLineArg = 1; 

    while( currentCommandLineArg < argc ) {
            char* currentArg = 
                        argv [ currentCommandLineArg ];
            debugLog(LOG_LEVEL_VERBOSE, 
                      "readCommandLineOptions():"
                      "looking at option %s", currentArg);

            bool found = false;
            bool predicateUsed = false;
            /* is the first character a '-' ? */
//            if( currentArg[0] == '-' ) {
  //              if( currentArg[1] == '-' ) {
                    /* long form */
/*
                    debugLog(LOG_LEVEL_VERBOSE, 
                            "readCommandLineOptions():"
                         "detected long form option in %s", 
                                              currentArg);
                    if(currentCommandLineArg + 1 < argc) {
                        if( readOption( currentArg+2, 
                                    longForm,
                            argv[currentCommandLineArg+1],
                                    &predicateUsed,
                                    commandLineOptionC,
                                    options )) {
                            found = true;
                        }
                    }
                    else {

                        if(readOption( currentArg+2, 
                                    longForm,
                                    NULL,
                                    &predicateUsed,
                                    commandLineOptionC,
                                    options )) {
                            found = true;
                        }
                    }
                }
            else {

                debugLog(LOG_LEVEL_VERBOSE, 
                        "readCommandLineOptions():"
                        "detected short form option in %s", 
                            currentArg);

                if(currentCommandLineArg + 1 < argc) {
                    found = readOption( currentArg+1, 
                                shortForm,
                        argv[currentCommandLineArg+1],
                                &predicateUsed,
                                commandLineOptionC,
                                options );
                }
                else {

                    found = readOption( currentArg+1, 
                                shortForm,
                                NULL,
                                &predicateUsed,
                                commandLineOptionC,
                                options );
                }
            }
             
        }

        if(!found) {

            debugLog(LOG_LEVEL_WARNING, 
                 "readCommandLineOptions():"
                 "not able to process %s", currentArg);
            return false;
            }

        if(predicateUsed) { */
            /* increment to move focus pass the consumed
             * predicate. */ /*
            currentCommandLineArg++;
        }
        currentCommandLineArg++;
    }
*/
    return true;
}

/* ------------------ readOption() ------------------------
 * to be frank, this function is mostly added to reduce
 * the indenting in readCommandLineOptions().
 * return values:
 *     true: option found and processed.
 *     false: option not found.
 * predicateUsed 'return' value:
 *     true: the predicate was present and used.
 *         eg. option="width", predicate="10"
 *     false: no predicate was used, option was binary
 *         eg. option="nowrap" -- nothing else needed
 */

/* for reference:
   enum optionType { longForm, shortForm } */

bool readOption( const char* option,
             enum optionType type,
                 const char* predicate,
                       bool* predicateUsed,
                         int commandLineOptionC,           
                      struct commandLineOption options[]) {
    bool problemInSettingSetting = false;
/*
    if( predicate ) {
        debugLog(LOG_LEVEL_VERBOSE, 
        "readOption():starting looking for %s, "
                 " predicate %s.", 
                             option, predicate);
    }
    else {
        debugLog(LOG_LEVEL_VERBOSE, 
        "readOption():starting looking for %s, "
                  "no predicate.", 
                             option);
    }

    switch( type ) {
        case longForm:
            if( strcmp( option, "help") == 0 ) {
                debugLog(LOG_LEVEL_VERBOSE, 
                "readOption():user wants help menu.");
                return false;
            }
            break;
        case shortForm:
            if( strcmp( option, "h") == 0 ) {
                debugLog(LOG_LEVEL_VERBOSE, 
                "readOption():user wants help menu.");
                return false;
            }
            break;
    }
    
    bool found = false;

    for(int i = 0 ; i < commandLineOptionC ; i++) {
        const char* optionI = NULL;
        if(type == longForm) {
            optionI = options[i].longForm; }
        else {
            optionI = options[i].shortForm; 
        }
    
        if(isSubstring( optionI, option )) {
            if( options[i].dataType[0] == 'b' ) {
                options[i].currentValueString = "true";
                debugLog(LOG_LEVEL_VERBOSE, 
                        "readOption():set %s to %s.", 
                             optionI, 
                             options[i].currentValueString);
                int setSettingReturn = 
                    options[i].setSetting( 
                        options[i].currentValueString );
                if(!setSettingReturn) {
                    problemInSettingSetting = true;

                    debugLog(LOG_LEVEL_WARNING, 
                        "readOption():could not set %s "
                                    "to %s.", 
                             optionI, 
                             options[i].currentValueString);
                    }
                found=true;
                *predicateUsed = false;
                }
            else {
                if( predicate) {
                    options[i].currentValueString = 
                       predicate;
                        debugLog(LOG_LEVEL_VERBOSE, 
                        "readOption():set %s to %s.", 
                             optionI, 
                             options[i].currentValueString);
                    found=true;
                    int setSettingReturn = 
                        options[i].setSetting( 
                         options[i].currentValueString );

                    if(!setSettingReturn) {
                        problemInSettingSetting = true;

                        debugLog(LOG_LEVEL_WARNING, 
                        "readOption():could not set %s "
                                    "to %s.", 
                             optionI, 
                             options[i].currentValueString);
                        }
                    *predicateUsed = true;
                }
            }
        }
    }
if(problemInSettingSetting) {
    return false;
    }
return found;*/
}

/* --------------------- Works Cited -------------------- */
/* 
 * GeeksforGeeks, KartheekMudarakola, adnanirshad158, &
 *      tarun18tk. (2022). "Enumeration (or enum) in C."
 *      GeeksforGeeks.org.  Retrieved from
 *      https://www.geeksforgeeks.org/enumeration-enum-c/ on
 *      2022 June 23.
 * Institute of Electrical and Electronics Engineers, Inc, &
 *      The Open Group. (2018). "stdbool.h(0p) — Linux
 *      manual page." GNU Linux.  Retrieved from
 *      https://man7.org/linux/man-
 *      pages/man0/stdbool.h.0p.html on 2022 July 16.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 */
