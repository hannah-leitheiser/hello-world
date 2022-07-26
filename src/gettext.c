#include <libintl.h> /* [ Fleury, 2016 ] */
#include <locale.h>  /* [ Fleury, 2016 ] */
#include <stdlib.h>

#include <stdio.h>
#include <config.h>

#include "hello_world.h"

#include "gettext.h"

void LanguageLocalizationInit( void ) {

  setlocale (LC_ALL, "");  
//  printf("%s %s\n", PACKAGE, getenv("PWD"));
  bindtextdomain (PACKAGE, getenv("PWD"));
  textdomain (PACKAGE);
}
