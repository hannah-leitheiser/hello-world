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

bool readCommandLineOptions( int commandLineOptionC, 
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
    //printf("optopt: %c\n", optopt);
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
    //printf("%s\n", options[option_index].longForm );
    

}



    return true;
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
