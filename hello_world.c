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

#include "hello_world.h"
#include "printf.c"
#include "messages.c"
#include "command_line_args.c"
#include "gettext.c"
#include "debug_log.c"
#include "word_wrap.c"

/******************* int main() **************************
 * Outpus "Hello World!" to stdout -- likely as text to 
 * the terminal.
 * [function similar to Kernighan & Ritchie, 1998, p. 6] */

const char* programName;
/* https://stackoverflow.com/questions/12189480/why-structs-cannot-be-assigned-directly */
struct commandLineOption commandLineOptions[] = {
    (struct commandLineOption){"w", "width", "Terminal Width in Columns for Word Wrap\n0 for autodetect", "int", "0" },
    (struct commandLineOption){"n", "nowrap", "Disable Word Wrap", "bool", "false" },
    (struct commandLineOption){"l", "lang", "Language", "string", "" },
    (struct commandLineOption){"d", "debug", "Debug Level:\n0 Error\n1 Warning\n2 Verbose", "string", "0" } };
const int commandLineOptionCount = 4;


void greetWorld() {
        printf( 
            wrapText( 
               helloMessage(), 0 )
            ); /* if no command-line argument is */
        }



int main(int argc, char *argv[]) { /* [from WG14, 2018, p. 11] */
    setDebugLogOutput( stdout );
    debugLog( LOG_LEVEL_VERBOSE, "main():Entering function." );

    if(argc > 0) {
        debugLog( LOG_LEVEL_VERBOSE, "main():Saving program name \"%s\" from command line arguments.", argv[0] );
        programName = argv[0];
    }    

  if(argc == 1) {
        debugLog( LOG_LEVEL_VERBOSE, "main():No user-supplied command line arguments, printing hello message." );
        greetWorld(); /* if no command-line argument is */
                           /* supplied. */
    }
  else {
    int optionReadSuccess = readCommandLineOptions( commandLineOptionCount, commandLineOptions, argc, argv );


        int level;
        sscanf(commandLineOptions[3].currentValueString, "%d\n", &level);
        setDebugLogLevel( level );

        int width;
        sscanf(commandLineOptions[0].currentValueString, "%d\n", &width);
        wrapColumns = width;

        debugLog( LOG_LEVEL_VERBOSE, "main():read width %d", width );
        noWrap = commandLineOptions[1].currentValueString[0] == 't';


if(!optionReadSuccess) {
        printf( helpMessage( programName, commandLineOptionCount, commandLineOptions ));  /* if any unlised command-line argument is */
        }
    if(optionReadSuccess) {



        

        greetWorld();
        }

                           /* supplied.  */

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

/*  Works Cited:
 *  WG14. (2018).  Programming Languages -- C. 9899:202x (E).  ISO/IEC.
 *     Retrieved from https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf
 *     on 2022 June 03.
 *  Kernighan, Brian W. & Ritchie, Dennis M.  (1988).  The C Programming Language.  
 *     Second Edition.  Prentise Hall.  ISBN 0-13-110370-9. 
 *  Thompson, Keith.  2012.  "Should I return EXIT_SUCCESS or 0 
 *     from main()?: Answer."  Stack Overflow.  
 *     Retrieved from 
 *     https://stackoverflow.com/questions/8867871/should-i-return-exit-success-or-0-from-main
 *     on 2022 June 03.
 */
