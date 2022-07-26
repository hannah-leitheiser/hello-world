/* Filename        : configuration_file.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Parse a configuration file into
 *                 : pseudo command-line arguments.
 *                 : eg. width=10 becomes --width 10,
 *                 : then send those strings to
 *                 : readCommandLineOptions() for
 *                 : processing.
 * ( Kernighan & Ritchie, 1988, p. 9: Comment Syntax ) */

#define _GNU_SOURCE /* ( Brouwer, 2001, Synopsis )        */ 
#include <stdio.h>  /* ( Brouwer, 2001, Synopsis )        */
#include <stdlib.h> /* (Koenig & Kerrisk, 2018, Synopsis) */
#include <stdbool.h>/* (IEEE, Inc & The Open Group, 2018) */

#include "command_line_args.h"
#include "debug_log.h"

#include "configuration_file.h"

/* --------------- readConfigurationFile() -----------------
 * Parse a configuration file into pseudo command-line 
 * arguments.  
 *     eg. width=10 becomes --width 10
 * Then send those strings toreadCommandLineOptions() for
 * processing.
 * Return Values
 *     true -- success.
 *     false -- failure. */

/* ( Walia et. al., n.d.: a general reference ) */

/* for reference

struct commandLineOption {                                   
    char* shortForm;                                         
    char* longForm;                                          
    char* description;                                       
    char* dataType;                                          
    char* currentValueString;                                
    bool (*setSetting)(const char*);                         
    };  */

bool readConfigurationFile(FILE* file,                        
  int commandLineOptionC,                                    
        struct commandLineOption options[]) {

    debugLog(LOG_LEVEL_VERBOSE, 
                      "readConfigurationFile():"
                      "entering function." );

    ssize_t read; /* ( mbaotpff & gsamaras, 2018 ) */
    char* line = NULL; /* ( mbaotpff & gsamaras, 2018 ) */
    size_t len = 0; /* ( mbaotpff & gsamaras, 2018 ) */
    char* argument = "";
    char* predicate = "";

    while ((read = getline(&line, &len, file)) != -1) {
        /* (mbaotpff & gsamaras, 2018: similar code ) */
        argument = "--";
        predicate = "";

        /* find the "=" */
        int equalIndex = 0;
        for( ; line[equalIndex] != '=' && 
               line[equalIndex] != '\n' && 
               line[equalIndex] != '\0' ; 
                 equalIndex++) {
            char* toFree = argument;
            if ( asprintf( &argument, "%s%c", argument, 
                        line[equalIndex] ) == -1) {
                /* ( Brouwer, 2001, Return Value ) */
                debugLog(LOG_LEVEL_WARNING, 
                      "readConfigurationFile():"
                      "unsuccessful using asprintf() "
                      "to save argument %s%c to a string. "
                      "Exiting function.",
                      argument, line[equalIndex] ); 
                return false;
            }
            if( equalIndex > 1) {
                /* free memory, but not the string literal
                   "--" */ 
                free( toFree );
            }
        }
        if(line[equalIndex] == '=') {
            equalIndex++;
            int equalIndexBegin = equalIndex;

            for( ; line[equalIndex] != '=' && 
                   line[equalIndex] != '\n' && 
                   line[equalIndex] != '\0' ; 
                         equalIndex++) {
                char* toFree = predicate;
                if( asprintf( &predicate, "%s%c", 
                    predicate, line[equalIndex] ) == -1) {
                
                    /* ( Brouwer, 2001, Return Value ) */
                    debugLog(LOG_LEVEL_WARNING, 
                      "readConfigurationFile():"
                      "unsuccessful using asprintf() "
                      "to save predicate %s%c to a string. "
                      "Exiting function.",
                      predicate, line[equalIndex] ); 
                return false;
                }
                if( equalIndex > equalIndexBegin+ 1) {
                    /* again we need to avoid freeing the
                     * string literal "" */
                    free( toFree );
                }
            }
        
            char* argv[] = { "", argument, predicate };
            int argc = 3;
            if( !readCommandLineOptions(commandLineOptionC, 
                                  options, argc, argv) ) {
                debugLog(LOG_LEVEL_WARNING, 
                      "readConfigurationFile():"
                      "unsuccessful parse of %s %s. "
                      "Exiting function.",
                      argument, predicate);
                return false;
            }

        }

        else {
            char* argv[] = { "", argument  };
            int argc = 2;
            if( !readCommandLineOptions(commandLineOptionC, 
                                     options, argc, argv)) {
                debugLog(LOG_LEVEL_WARNING, 
                      "readConfigurationFile():"
                      "unsuccessful parse of %s, "
                      "(no predicate). "
                      "Exiting function.",
                      argument);
                return false;
            }

        }
    
        free(line);
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
 * Koenig, Thomas & Kerrisk, Michael. (2018). "malloc(3) —
 *      Linux manual page." GNU Linux.  Retrieved from
 *      https://man7.org/linux/man-pages/man3/malloc.3.html
 *      on 2022 July 14.
 * Walia, D., Jonny, Goel, R., & Yogesh. (n.d.). "C read
 *      file." Programmingsimplified.  Retrieved from
 *      https://www.programmingsimplified.com/c-program-
 *      read-file on 2022 June 20.
 * mbaitoff & gsamaras. (2018). "C read file line by line:
 *      Answer." Stackoverflow.  Retrieved from
 *      https://stackoverflow.com/questions/3501338/c-read-
 *      file-line-by-line on 2022 June 20.
 */
