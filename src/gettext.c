#include <libintl.h> /* [ Fleury, 2016 ] */
#include <locale.h>  /* [ Fleury, 2016 ] */
#include <stdlib.h>

#include "hello_world.h"

#include "gettext.h"

void LanguageLocalizationInit( void ) {

  setlocale (LC_ALL, "");
  bindtextdomain (PACKAGE, LOCALE_DIR);
  textdomain (PACKAGE);
}
