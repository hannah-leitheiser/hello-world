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
#define _GNU_SOURCE  
#include <stdio.h>
#include <stdlib.h>
#include "command_line_args.h"
#include "debug_log.h"

#include "configuration_file.h"

/* for reference
struct commandLineOption {
    char* shortForm;
    char* longForm;
    char* description;
    char* dataType;
    char* currentValueString;
    };
    */

int readConfigurationFile(FILE* file,                        
  int commandLineOptionC,                                    
        struct commandLineOption options[]) {

/* https://www.programmingsimplified.com/c-program-read-file */
//fseek(file, 0L, SEEK_END); 
char ch;
 ssize_t read;
char * line = NULL;
 size_t len = 0;
char* argument = "";
char* predicate = "";

/* https://stackoverflow.com/questions/3501338/c-read-file-line-by-line */
while ((read = getline(&line, &len, file)) != -1) {
        argument = "--";
        predicate = "";

        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);
        /* find the "=" */
        int equalIndex = 0;
        for( ; line[equalIndex] != '=' && line[equalIndex] != '\n' && line[equalIndex] != '\0' ; equalIndex++) {
            asprintf( &argument, "%s%c", argument, line[equalIndex] );
        }
        if(line[equalIndex] == '=')
        {
        equalIndex++;

        for( ; line[equalIndex] != '=' && line[equalIndex] != '\n' && line[equalIndex] != '\0' ; equalIndex++) {
            asprintf( &predicate, "%s%c", predicate, line[equalIndex] );
        }
        
        char* argv[] = { "", argument, predicate };
        int argc = 3;
            readCommandLineOptions(commandLineOptionC, options, argc, argv);

        }

        else
        {

        char* argv[] = { "", argument  };
        int argc = 2;
            readCommandLineOptions(commandLineOptionC, options, argc, argv);

        }


        }



    } 

