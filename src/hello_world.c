/* Filename        : hello_world.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * File Summary    : Contains main() and specifies command
 *                 : line arguments.
 * (C Comment Syntax: 
         Kernighan & Ritchie, 1988, p. 9) */

#include <stdbool.h> /*(IEEE, Inc & The Open Group, 2018) */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* GNULib*/
#include "../lib/progname.h" /* ( Haertel, et. al., 2022, 
                           src/hello.c, line 32 ) */

/* src/ headers */

#include "hello_world.h"
#include "printf.h"
#include "messages.h"
#include "command_line_args.h"
#include "configuration_file.h"
#include "gettext.h"
#include "debug_log.h"
#include "word_wrap.h"

const char* programName; 
bool displayHelp = false;
bool displayVersion = false;
             /* ( Parahar, 2020: const char* meaning ) */

/* --------- settings and command line options ---------- */

struct helloWorldSettings settings =        /*  initial  */
   (struct helloWorldSettings)              /* settings  */
      { AUTODETECT,      /* text wrap width         */
        "",              /* system default language */
      };


bool getHelp( const char* _ );
bool getVersion( const char* _ );

bool settingsSetWidth( const char* width );
bool settingsSetNoWrap( const char* _ );
bool settingsSetLanguage( const char* lang );

#ifdef DEBUG_LOG
bool settingsSetDebugLogLevel( const char* level );
bool settingsSetDebugLogOutput( const char* output );
#endif

struct commandLineOption commandLineOptions[] = {
    (struct commandLineOption)
        {"w", "width", 
       "Terminal Width in Columns for Word Wrap\n"
       "0 for autodetect", 
       true, 
       true, 
       false,
       "",
       &settingsSetWidth },
    (struct commandLineOption){"n", "nowrap", 
       "Disable Word Wrap", 
       false, 
       false,
       false,
       "",
       &settingsSetNoWrap },
    (struct commandLineOption){"l", "lang", 
       "Language",
       true, 
       true,
       false,
       "",
       &settingsSetLanguage },
 
    (struct commandLineOption){"v", "version", 
       "Version Information", 
       false, 
       false, 
       true,
       "",
       &getVersion },


    #ifdef DEBUG_LOG
    
    (struct commandLineOption){"o", "debugoutput", 
       "Debug output:\n"
        "0 for standard output\n"
        "otherwise a filename", 
          true,
          true,
          false, 
          "",
          &settingsSetDebugLogOutput },
    (struct commandLineOption){"d", "debuglevel", 
        "Debug Level:\n"
            "0 Error\n"
            "1 Warning\n"
            "2 Verbose", 
            true,
            true,
            false, 
            "",
            &settingsSetDebugLogLevel },
    #endif

    (struct commandLineOption){"h?", "help", 
       "Get Help Message", 
       false, 
       false, 
       true,
       "",
       &getHelp }

            };
    /* ( Berger, 2012, struct literal format ) */
    /* ( Fisher, 2016, multi-line string format ) */  

const int commandLineOptionCount = 
          sizeof( commandLineOptions ) / 
                  sizeof(struct commandLineOption);

bool settingsSetWidth( const char* widthString ) {
if(!widthString || *widthString == '\0')
{
    settings.textWidth=0;
    return false;
}
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


#ifdef DEBUG_LOG

bool settingsSetDebugLogLevel( const char* levelString ) {
   int level;
   if( sscanf(levelString, 
     "%d\n", &level) ) {
        debugLog( LOG_LEVEL_VERBOSE, 
           "settingsSetDebugLogLevel():Setting level %d.",
                level );
        return setDebugLogLevel( level ) == level;
   }
   else {
       debugLog( LOG_LEVEL_WARNING, 
           "settingsSetDebugLogLevel():Level %s not "
              "recognized.",
                levelString );
       return false;
   }
}

bool settingsSetDebugLogOutput( const char* output ) {
    /* ( Parewa Labs, n.d., C strcmp() ) */
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


#endif

bool getHelp( const char* _ ) {
        debugLog( LOG_LEVEL_VERBOSE, 
           "getHelp():displayHelp = true;\n");
	displayHelp = true;
}


bool getVersion( const char* _ ) {
        debugLog( LOG_LEVEL_VERBOSE, 
           "getVersion():displayVersion = true;\n");
	displayVersion = true;
}

/* ---------------- greetWorld() ------------------------ *
 *
 * Print an appropriate greeting.
 * Return value:
 *  true  - success
 *  false - failure */

bool greetWorld( int width) {
    return printf( 
         
               helloMessage(width)); 
}


/* ------------------- showHelp() ------------------------ *
 *
 * Print help message.
 * Return value:
 *  true  - success
 *  false - failure */

bool showHelp(    const char* programName, 
                                    int commandLineOptionC, 
               struct commandLineOption options[], 
                                    int width) {
	const char* helpM = 
                helpMessage(  programName, 
                         commandLineOptionCount, 
                         commandLineOptions, 
                          width );  
        if( helpM ) {
        	return printf( helpM );
            }
        else {
		return false;
            }

}


/* ---------------- showVersion() ------------------------ *
 *
 * Print version info.
 * Return value:
 *  true  - success
 *  false - failure */

bool showVersion( int width ) {
	const char* versionM = 
                versionMessage( width );  
    if( versionM ) {
        	return printf( versionM );
    }
    else {
		return false;
    }

}

/* --------------------- main() ------------------------- */

int main(int argc, char *argv[]) { 
          /* from ( WG14, 2018, p. 11 ) */
    
    setDebugLogOutput( stdout );
    debugLog( LOG_LEVEL_VERBOSE, 
                     "main():Entering function." );

    FILE* configurationFile = fopen(CONFIGURATION_FILE
                                                  , "r");
    if( configurationFile ) {
        if( !readConfigurationFile(configurationFile,                        
             commandLineOptionCount,                                    
               commandLineOptions)) { 
        debugLog( LOG_LEVEL_WARNING, 
            "main():error in configuration file." );
        }
        fclose( configurationFile ); 
    }
    else {
        debugLog( LOG_LEVEL_WARNING, 
            "main():Unable to read configuration file." );
    }


	if(displayHelp) {
        debugLog( LOG_LEVEL_WARNING, 
            "main():Configuration file triggered help." );
    }
    LanguageLocalizationInit();

    if(argc > 0) {
        debugLog( LOG_LEVEL_VERBOSE, 
             "main():Saving program name \"%s\" "
                 "from command line arguments.", argv[0] );
        set_program_name( argv[0] );
              /* ( Haertel, et. al., 2022, src/hello.c, 
                   line 137 ) */
        programName = program_name;
    }    


	bool optionReadSuccess = 
	     readCommandLineOptions(
		  commandLineOptionCount, 
		  commandLineOptions, argc, argv );

	    /* if any unlised command-line argument is 
	       supplied.  By not putting --help in the 
	       options list, it will trigger this message.*/
	if(!optionReadSuccess | displayHelp) {

		if(!showHelp( programName, 
			      commandLineOptionCount, 
			      commandLineOptions, 
			      settings.textWidth)) {
			aBadEnd();
			}

    		debugLog( LOG_LEVEL_VERBOSE, 
                 "main():help displayed, EXIT_SUCCESS" );
    		return EXIT_SUCCESS;  
	}
	if(displayVersion) {
		if(!showVersion( settings.textWidth)) {
				aBadEnd();
			}
    		debugLog( LOG_LEVEL_VERBOSE, 
                  "main():version displayed, EXIT_SUCCESS");
    		return EXIT_SUCCESS;
	}  

    greetWorld( settings.textWidth );

    debugLog( LOG_LEVEL_VERBOSE, 
         "main():said hello, EXIT_SUCCESS" );
    return EXIT_SUCCESS;  
                /* ( WG14, 2018, p. 11, program exit. ) */
}

/* -------------------- aBadEnd() ----------------------- *
 *
 * "You are having a bad problem and will not go to space 
 * today." - ( Munroe, 2012 )
 *
 * Sadly, we failed to greet the world.  Let the user know
 * this program is aborting. */

void aBadEnd(void) {
    if(programName) {
        fprintf( stderr, _("Aborting %s.\n"), 
                 programName);
    }
    else {
        fprintf( stderr, _("Aborting.\n"));
    }
    debugLog( LOG_LEVEL_ERROR, 
             "aBadEnd():EXIT_FAILURE");
    exit( EXIT_FAILURE ); /* (Tutorials Point, 2022) */
}

/* --------------------- Works Cited -------------------- */
/* 
 * Berger, Avi. (2012). "Why structs cannot be assigned
 *      directly?: Answer." Stackoverflow.  Retrieved from
 *      https://stackoverflow.com/questions/12189480/why-
 *      structs-cannot-be-assigned-directly on 2022 June 03.
 * Fisher, James. (2016). "How do I write a multi-line
 *      string literal in C?." Website.  Retrieved from
 *      https://jameshfisher.com/2016/11/30/c-multiline-
 *      literal/ on 2022 June 14.
 * Institute of Electrical and Electronics Engineers, Inc, &
 *      The Open Group. (2018). "stdbool.h(0p) — Linux
 *      manual page." GNU Linux.  Retrieved from
 *      https://man7.org/linux/man-
 *      pages/man0/stdbool.h.0p.html on 2022 July 16.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 * Mike Haertel, David MacKenzie, Jan Brittenson, Roland
 *      McGrath, Charles Hannum, Bruce Korb, Karl
 *      Eichwalder, Karl Berry, & The King. (2022). "GNU
 *      Hello World." GNU Savanna.  Retrieved from
 *      https://ftp.gnu.org/gnu/hello/ on 2022 July 20.
 * Munroe, Randall. (2012). "Up Goer Five." XKCD.  Retrieved
 *      from https://xkcd.com/1133/ on 2022 July 19.
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
