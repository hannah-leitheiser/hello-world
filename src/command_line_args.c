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
    
/* Here we develop a structure that getopt.h will like */

/*  from getopt.h
/*   -   struct option {
     -             const char *name;
     -             int         has_arg;
     -             int        *flag;
     -             int         val;
     -         }; */
/* (Koenig & Kerrisk, 2008) */

/* I had originally written my own code to process command
     line arguments, but switched to getopt.h which will
     be more standard, but no less complicated.  */

struct option* getOptStruct = 
      malloc( sizeof( struct option) * 
                    (commandLineOptionC + 1 ) );

char* shortOptionString = ":";

for(int i = 0 ; i < commandLineOptionC ; i++) {
    getOptStruct[i].name = options[i].longForm;

    /* no_argument, required_argument, optional_argument
       are constants defined in getopt.h, pick the best
       one. */

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

    /* The getopt_long() return value will be used. */

    getOptStruct[i].flag=0;
    getOptStruct[i].val=0;

    /* generate an shortOptionString to pass to 
       getops_long() */

    for(int ii = 0 ; options[i].shortForm[ii] != '\0' ;
              ii++) {
        asprintf(&shortOptionString, "%s%c", 
             shortOptionString, 
                  options[i].shortForm[ii]);
        
        /* one colon for requires argument, 
           two for optional argument. */

        if( options[i].takesArgument) {

            asprintf(&shortOptionString, "%s%c", 
                  shortOptionString, ':');
        
            if( !options[i].requiresArgument) {

                asprintf(&shortOptionString, "%s%c", 
                shortOptionString, ':');
            }
        }

    }
}

/* "The last element of the array has to be filled with 
    zeros." - Koenig & Kerrisk, 2008. */

getOptStruct[ commandLineOptionC ] = (struct option){
    0, 0, 0, 0 };
    

#define UNSET -1
int getoptReturn;
int option_index = UNSET;
int longoption = UNSET;
while( (getoptReturn = getopt_long(argc, argv, 
              shortOptionString, getOptStruct, &longoption))
                        != -1) {
    
    /* log and unrecgonized option.  getoptReturn will
       be a question mark, which will trigger help. */

    if(optopt != NULL) {
        debugLog( LOG_LEVEL_VERBOSE,                         
           "readCommandLineOptions():optopt: %c.",   
                   (char)optopt);

    }
    else {
        debugLog( LOG_LEVEL_VERBOSE,                         
           "readCommandLineOptions():optopt=NULL.",   
                   optopt);
    }

    if(getoptReturn == 0) {
        debugLog( LOG_LEVEL_VERBOSE,                         
           "readCommandLineOptions():getoptReturn=0.");
        }
    
     /* if longoption was not set, check ourselves to find
        which short option coresponds to the return value
        */
     if(longoption == UNSET) {

        debugLog( LOG_LEVEL_VERBOSE,                         
           "readCommandLineOptions():getoptReturn(n)=%d,"
            " (c)=%c.", getoptReturn, (char)getoptReturn);

        for(int i = 0 ; i < commandLineOptionC ; i++) {
        
            for(int ii = 0 ; 
                  options[i].shortForm[ii] != '\0' ;
                        ii++) {
                if(getoptReturn == 
                           options[i].shortForm[ii]) {
                    option_index = i;
                }
            }
          } 
      }
      else {
         option_index = longoption; 
      }
     
    if(option_index >= 0) {
   

     debugLog( LOG_LEVEL_VERBOSE,                         
           "readCommandLineOptions():optarg: %s.",   
                   optarg);
    
    /* We're dealing with string pointers, which will
       probably get overwritten when the next argument
       is processed.  */

    char* optarg_static;
    asprintf(&optarg_static, "%s", optarg); 
    options[option_index].argument = optarg_static;

    /* Execute the function to process the command line
       option. */

    int setSettingReturn = 
                        options[option_index].setSetting( 
                         options[option_index].argument );
     }
    
longoption=UNSET;
}



    return true;
}
/* --------------------- Works Cited -------------------- */
/* 
 * Brouwer, Andries. (2001). "asprintf(3) — Linux manual
 *      page." GNU Linux.  Retrieved from
 *      https://man7.org/linux/man-
 *      pages/man3/asprintf.3.html on 2022 June 25.
 * Institute of Electrical and Electronics Engineers, Inc, &
 *      The Open Group. (2018). "stdbool.h(0p) — Linux
 *      manual page." GNU Linux.  Retrieved from
 *      https://man7.org/linux/man-
 *      pages/man0/stdbool.h.0p.html on 2022 July 16.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 * Koenig, Thomas & Kerrisk, Michael. (2008). "getopt(3) —
 *      Linux manual page." GNU Linux.  Retrieved from
 *      https://www.man7.org/linux/man-
 *      pages/man3/getopt.3.html on 2022 July 22.
 */
