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

#include "hello_world.h"
#include "printf.h"
#include "messages.h"
#include "command_line_args.h"
#include "gettext.h"
#include "debug_log.h"
#include "word_wrap.h"

const char* programName; 
             /* ( Parahar, 2020, const char* meaning ) */

struct commandLineOption commandLineOptions[] = {
    (struct commandLineOption){"w", "width", 
       "Terminal Width in Columns for Word Wrap\n"
       "0 for autodetect", "int", "0" },
    (struct commandLineOption){"n", "nowrap", 
       "Disable Word Wrap", "bool", "false" },
    (struct commandLineOption){"l", "lang", 
       "Language", "string", "" },
    (struct commandLineOption){"d", "debug", 
        "Debug Level:\n"
            "0 Error\n"
            "1 Warning\n"
            "2 Verbose", "string", "0" } };
    /* ( Berger, 2012, struct literal format ) */
const int commandLineOptionCount = 
          sizeof( commandLineOptions ) / 
                  sizeof(struct commandLineOption);

/* ----------------------------- greetWorld() ----------------------------------- */

bool
 greetWorld() {
        return printf( 
            wrapText( 
               helloMessage(), 0 )
            ); 
        }

/* ----------------------------- main() ----------------------------------- */

int main(int argc, char *argv[]) { /* ( WG14, 2018, p. 11 ) */

    setDebugLogOutput( stdout );
    debugLog( LOG_LEVEL_VERBOSE, "main():Entering function." );

    if(argc > 0) {
        debugLog( LOG_LEVEL_VERBOSE, "main():Saving program name \"%s\" from command line arguments.", argv[0] );
        programName = argv[0];
    }    

  if(argc == 1) {
        debugLog( LOG_LEVEL_VERBOSE, "main():No user-supplied command line arguments, printing hello message." );
        greetWorld();                    
    }
  else {
    int optionReadSuccess = readCommandLineOptions( commandLineOptionCount, commandLineOptions, argc, argv );


        int level;
        sscanf(commandLineOptions[3].currentValueString, "%d\n", &level);
        setDebugLogLevel( level );

        int width;
        sscanf(commandLineOptions[0].currentValueString, "%d\n", &width);
        setWrapWidth(  width );

        debugLog( LOG_LEVEL_VERBOSE, "main():read width %d", width );
        setNoWrap ( commandLineOptions[1].currentValueString[0] == 't' );


if(!optionReadSuccess) {
        printf( helpMessage( programName, commandLineOptionCount, commandLineOptions ));  /* if any unlised command-line argument is */
        }
    if(optionReadSuccess) {
        greetWorld();
        }


  }
  /* [if statement modeled after Kernighan & Richie, 1998, p. 20
          or similar ] */

    debugLog( LOG_LEVEL_VERBOSE, "main():EXIT_SUCCESS" );
  return EXIT_SUCCESS;  /* [program exit: WG14, 2018, p. 11,
                            EXIT_SUCCESS: Thompson, 2012 ] */
}

void aBadEnd(void) {
    if(programName) {
        fprintf( stderr, _("Aborting %s.\n"), programName);
    }
    else {
        fprintf( stderr, _("Aborting.\n"));
    }
    exit( EXIT_FAILURE ); /* https://www.tutorialspoint.com/c_standard_library/c_function_exit.htm */
}

/* -------------------- Works Cited -------------------- */
 /* 
 * Berger, Avi. (2012). "Why structs cannot be assigned
 *      directly?: Answer." Stackoverflow.  Retrieved from
 *      https://stackoverflow.com/questions/12189480/why-
 *      structs-cannot-be-assigned-directly on 2022 June 03.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition.." Prentise
 *      Hall..  ISBN 0-13-110370-9.
 * Parahar, Mahesh. (2020). "Difference between const char*
 *      p, char * const p, and const char * const p in C."
 *      Tutorialspoint.  Retrieved from
 *      https://www.tutorialspoint.com/difference-between-
 *      const-char-p-char-const-p-and-const-char-const-p-
 *      in-c on 2022 June 09.
 * Thompson, Keith. (2012). "Should I return EXIT_SUCCESS or
 *      0 from main()?: Answer." Stack Overflow..  Retrieved
 *      from
 *      https://stackoverflow.com/questions/8867871/should-
 *      i-return-exit-success-or-0-from-main on 2022 June
 *      03.
 * WG14. (2018). "Programming Languages -- C. 9899:202x
 *      (E)." ISO/IEC.  Retrieved from https://www.open-
 *      std.org/jtc1/sc22/wg14/www/docs/n2310.pdf on 2022
 *      June 03.
 */
