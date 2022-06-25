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
 * [Comment Syntax: Kernighan & Ritchie, 1988, p. 9] */

#include <stdbool.h>
#define _GNU_SOURCE  
#include <stdio.h>
#include <stdlib.h>
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

    ssize_t read; /* ( mbaotpff & gsamaras, 2018 ) */
    char* line = NULL; /* ( mbaotpff & gsamaras, 2018 ) */
    size_t len = 0; /* ( mbaotpff & gsamaras, 2018 ) */
    char* argument = "";
    char* predicate = "";

    /* https://stackoverflow.com/questions/3501338/c-read-file-line-by-line */
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
            asprintf( &argument, "%s%c", argument, 
                                 line[equalIndex] );
        }
        if(line[equalIndex] == '=') {
            equalIndex++;

            for( ; line[equalIndex] != '=' && 
                   line[equalIndex] != '\n' && 
                   line[equalIndex] != '\0' ; 
                         equalIndex++) {
            asprintf( &predicate, "%s%c", 
                       predicate, line[equalIndex] );
            }
        
            char* argv[] = { "", argument, predicate };
            int argc = 3;
            readCommandLineOptions(commandLineOptionC, 
                                  options, argc, argv);

        }

        else {
            char* argv[] = { "", argument  };
            int argc = 2;
            readCommandLineOptions(commandLineOptionC, 
                                     options, argc, argv);

        }
    }
} 

/* --------------------- Works Cited -------------------- */
/* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 * Walia, D., Jonny, Goel, R., & Yogesh. (n.d.). "C read
 *      file." Programmingsimplified.  Retrieved from
 *      https://www.programmingsimplified.com/c-program-
 *      read-file on 2022 June 20.
 * mbaitoff & gsamaras. (2018). "C read file line by line:
 *      Answer." Stackoverflow.  Retrieved from
 *      https://stackoverflow.com/questions/3501338/c-read-
 *      file-line-by-line on 2022 June 20.
 */
