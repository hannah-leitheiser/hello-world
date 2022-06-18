#include <libintl.h> /* [ Fleury, 2016 ] */
#include <locale.h>  /* [ Fleury, 2016 ] */
#include <stdlib.h>

#include "hello_world.h"

#include "gettext.h"

void LanguageLocalizationInit( void ) {

 putenv("LANGUAGE=de_DE.UTF8");
  
  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);
}
