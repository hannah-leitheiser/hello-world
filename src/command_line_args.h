/* Filename        : command_line_args.h
 * Type of File    : C Source Code, Header
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Process command line arguments based
 *                 : on a struct which specifies the
 *                 : arguments and responses.
 * (Kernighan & Ritchie, 1988, p. 9, command syntax)
 * (Borini & Smith, 2009, project file breakdown) */

#ifndef __COMMAND_LINE_ARGS_H  /* (cschol, 2008, guard) */
#define __COMMAND_LINE_ARGS_H

#include <stdbool.h>

struct commandLineOption {
    const char* shortForm;
    const char* longForm;
    const char* description;
    const char* dataType;
    const char* currentValueString;
    bool (*setSetting)(const char*);
    };

/* ( Parewa Labs, n.d., C struct ) */ 
/* ( GeeksforGeeks, 2018 ) */

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

bool readCommandLineOptions(int commandLineOptionC, 
                        struct commandLineOption options[], 
                           int argc, 
                         char *argv[]);

#endif

/* --------------------- Works Cited -------------------- */
/* 
 * GeeksforGeeks. (2018). "Function Pointer in C."
 *      GeeksforGeeks.org.  Retrieved from
 *      https://www.geeksforgeeks.org/function-pointer-in-c/
 *      on 2022 June 23.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 * Parewa Labs. (n.d.). "C struct." Parewa Labs Pvt. Ltd..
 *      Retrieved from
 *      https://www.programiz.com/c-programming/c-structures
 *      on 2022 June 14.
 * Smith, Jed & Borini, Stefano. (2009). "What do .c and .h
 *      file extensions mean to C?, Answer." Stackoverflow.
 *      Retrieved from
 *      https://stackoverflow.com/questions/1695224/what-do-
 *      c-and-h-file-extensions-mean-to-c on 2022 June 03.
 * cschol. (2008). "Organization of C files: Answer."
 *      Stackoverflow.  Retrieved from https://stackoverflow
 *      .com/questions/47919/organization-of-c-files on 2022
 *      June 03.
 */
