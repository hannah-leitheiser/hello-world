#include <libintl.h> /* [ Fleury, 2016 ] */
#include <locale.h>  /* [ Fleury, 2016 ] */

#ifndef __GETTEXT_H /* [guard modeled on cschol, 2008] */
#define __GETTEXT_H

#define _(STRING) (const char*)gettext(STRING) /* [ Fleury, 2016, Hello World! Example ] */ 

void LanguageLocalizationInit( void );

#endif
