/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : Print "Hello World!" to stdout.
 * Compile         : make
 *  and Run        : ./hello_world
 * (Comment Syntax: 
         Kernighan & Ritchie, 1988, p. 9) */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hello_world.h"
#include "printf.h"
#include "messages.h"
#include "command_line_args.h"
#include "configuration_file.h"
#include "gettext.h"
#include "debug_log.h"
#include "word_wrap.h"

#define DEBUG
#define CONFIGURATION_FILE "hello_world.conf"

const char* programName; 
             /* ( Parahar, 2020, const char* meaning ) */

/* --------- settings and command line options ---------- */

struct helloWorldSettings settings =        /*  initial  */
   (struct helloWorldSettings)              /* settings  */
      { AUTODETECT,      /* text wrap width         */
        "",              /* system default language */
      };

bool settingsSetWidth( const char* width );
bool settingsSetNoWrap( const char* _ );
bool settingsSetDebugLogLevel( const char* level );
bool settingsSetDebugLogOutput( const char* output );
bool settingsSetLanguage( const char* lang );

struct commandLineOption commandLineOptions[] = {
    (struct commandLineOption){"w", "width", 
       "Terminal Width in Columns for Word Wrap\n"
       "0 for autodetect", "int", "0", &settingsSetWidth },
    (struct commandLineOption){"n", "nowrap", 
       "Disable Word Wrap", "bool", "false",
                                    &settingsSetNoWrap },
    (struct commandLineOption){"l", "lang", 
       "Language", "string", "", &settingsSetLanguage },
    (struct commandLineOption){"o", "debugoutput", 
       "Debug output:\n"
        "0 for standard output\n"
        "otherwise a filename", 
          "string", "", &settingsSetDebugLogOutput },
(struct commandLineOption){"d", "debug", 
        "Debug Level:\n"
            "0 Error\n"
            "1 Warning\n"
            "2 Verbose", 
            "string", "0", &settingsSetDebugLogLevel } };
    /* ( Berger, 2012, struct literal format ) */
    /* ( Fisher, 2016, multi-line string format ) */  

const int commandLineOptionCount = 
          sizeof( commandLineOptions ) / 
                  sizeof(struct commandLineOption);

bool settingsSetWidth( const char* widthString ) {
    int width;
    if(sscanf(widthString, 
                        "%d\n", &width)) {
        debugLog( LOG_LEVEL_VERBOSE, 
                "settingsSetWidth():width to %d.", width );
        settings.textWidth = width;
        return true;
    }
    return false;
}

bool settingsSetNoWrap( const char* _ ) {
    settings.textWidth = NOWRAP;
    debugLog( LOG_LEVEL_VERBOSE, 
              "settingsSetNoWrap():Nowrap Set." );
    return true;
}

bool settingsSetDebugLogLevel( const char* levelString ) {
   int level;
   if( sscanf(levelString, 
     "%d\n", &level) ) {
        debugLog( LOG_LEVEL_VERBOSE, 
           "settingsSetDebugLogLevel():Setting level %d.",
                level );
        return setDebugLogLevel( level );
   }
return false;
}

bool settingsSetLanguage( const char* lang ) {
    if(lang) {
        debugLog( LOG_LEVEL_VERBOSE, 
           "settingsSetLanguage():Language to %s.",
                lang );
        settings.specifiedLanguage = lang;
        return true;
    }
return false;
}


bool settingsSetDebugLogOutput( const char* output ) {
    /* ( Parewa Labs, n.d. ) */
    if( strcmp( output, "0" ) == 0) { 
        debugLog( LOG_LEVEL_VERBOSE, 
           "settingsSetDebugLogOutput():STDOUT.");
        setDebugLogOutput( stdout );
        return true;
        }
    else {
        if(output) {
            FILE* f = fopen( output, "w");
            if(f) {
                setDebugLogOutput( f );

                debugLog( LOG_LEVEL_VERBOSE, 
               "settingsSetDebugLogOutput():file \"%s\".",
                  output );
                return true;
            }
            else {

                debugLog( LOG_LEVEL_WARNING, 
                      "settingsSetDebugLogOutput():"
                       "unable to create \"%s\"," 
                       "not setting debug output",
                             output );
                return false;
            }
        }
    }
}


/* ---------------- greetWorld() ------------------------ *
 *
 * Print an appropriate greeting.
 * Return value:
 *  true  - success
 *  false - failure */

bool greetWorld( int width) {
    return printf( 
        wrapText( 
               helloMessage(), width, "", "" )
                    ); 
}

/* --------------------- main() ------------------------- */

int main(int argc, char *argv[]) { 
          /* from ( WG14, 2018, p. 11 ) */

    debugLog( LOG_LEVEL_VERBOSE, 
                     "main():Entering function." );

    FILE* configurationFile = fopen(CONFIGURATION_FILE
                                                  , "r");
    if( configurationFile ) {
        readConfigurationFile(configurationFile,                        
             commandLineOptionCount,                                    
               commandLineOptions);   
    }
    else {
        debugLog( LOG_LEVEL_WARNING, 
            "main():Unable to read configuration file." );
    }

    if(argc > 0) {
        debugLog( LOG_LEVEL_VERBOSE, 
             "main():Saving program name \"%s\" "
                 "from command line arguments.", argv[0] );
        programName = argv[0];
    }    


    if(argc == 1) {
        debugLog( LOG_LEVEL_VERBOSE, 
          "main():No user-supplied command line arguments, "
          "printing hello message." );
        greetWorld( settings.textWidth );                    
    }
    else {
        bool optionReadSuccess = 
             readCommandLineOptions( 
                  commandLineOptionCount, 
                  commandLineOptions, argc, argv );

            /* if any unlised command-line argument is 
               supplied.  By not putting --help in the 
               options list, it will trigger this message.*/
        if(!optionReadSuccess) {
            printf(   helpMessage(  programName, 
                         commandLineOptionCount, 
                         commandLineOptions, 
                          settings.textWidth ));  
        }
    if(optionReadSuccess) {
        greetWorld( settings.textWidth );
        }


    }

    debugLog( LOG_LEVEL_VERBOSE, "main():EXIT_SUCCESS" );
    return EXIT_SUCCESS;  
                /* ( WG14, 2018, p. 11, program exit. ) */
}

/* -------------------- aBadEnd() ----------------------- *
 * Sadly, we failed to greet the world.  Let the user know
 * this program is aborting. */

void aBadEnd(void) {
    if(programName) {
        fprintf( stderr, _("Aborting %s.\n"), programName);
    }
    else {
        fprintf( stderr, _("Aborting.\n"));
    }
    debugLog( LOG_LEVEL_ERROR, "aBadEnd():EXIT_FAILURE");
    exit( EXIT_FAILURE ); /* (Tutorials Point, 2022) */
}

/* -------------------- Works Cited -------------------- */
/* 
 * Berger, Avi. (2012). "Why structs cannot be assigned
 *      directly?: Answer." Stackoverflow.  Retrieved from
 *      https://stackoverflow.com/questions/12189480/why-
 *      structs-cannot-be-assigned-directly on 2022 June 03.
 * Fisher, James. (2016). "How do I write a multi-line
 *      string literal in C?." Website.  Retrieved from
 *      https://jameshfisher.com/2016/11/30/c-multiline-
 *      literal/ on 2022 June 14.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition.." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 * Parahar, Mahesh. (2020). "Difference between const char*
 *      p, char * const p, and const char * const p in C."
 *      Tutorialspoint.  Retrieved from
 *      https://www.tutorialspoint.com/difference-between-
 *      const-char-p-char-const-p-and-const-char-const-p-
 *      in-c on 2022 June 09.
 * Parewa Labs. (n.d.). "C strcmp()." Parewa Labs Pvt. Ltd..
 *      Retrieved from
 *      https://www.programiz.com/c-programming/library-
 *      function/string.h/strcmp on 2022 June 14.
 * Tutorials Point. (2022). "C library function - exit()."
 *      Tutorials Point.  Retrieved from https://www.tutoria
 *      lspoint.com/c_standard_library/index.htm on 2022
 *      June 14.
 * WG14. (2018). "Programming Languages -- C. 9899:202x
 *      (E)." ISO/IEC.  Retrieved from https://www.open-
 *      std.org/jtc1/sc22/wg14/www/docs/n2310.pdf on 2022
 *      June 03.
 */
