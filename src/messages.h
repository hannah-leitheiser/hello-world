/* Filename        : messages.h
 * Type of File    : C Source Code, Header
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * File Summary    : Provide appropriate character strings
                   : for "Hello World!" and --help.
 * (C Comment Syntax: Kernighan & Ritchie, 1988, p. 9) */

#ifndef __MESSAGES_H /* [guard modeled on cschol, 2008] */
#define __MESSAGES_H

#include "command_line_args.h"

/* returns greeting string -- probably "Hello World!" */

const char* helloMessage(void);

/* returns response to command line argument to --help or
   the response when an unrecgonized command line argument
   is supplied */

const char* helpMessage( const char* programName, 
                                 int commandLineOptionC, 
                        struct commandLineOption options[], 
                                 int width);
#endif

/* --------------------- Works Cited -------------------- */
/* 
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 * cschol. (2008). "Organization of C files: Answer."
 *      Stackoverflow.  Retrieved from https://stackoverflow
 *      .com/questions/47919/organization-of-c-files on 2022
 *      June 03.
 */
