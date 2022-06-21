#include <libintl.h> /* [ Fleury, 2016 ] */
#include <locale.h>  /* [ Fleury, 2016 ] */

#ifndef __GETTEXT_H /* [guard modeled on cschol, 2008] */
#define __GETTEXT_H

#define _(STRING) (const char*)gettext(STRING) /* [ Fleury, 2016, Hello World! Example ] */ 

void LanguageLocalizationInit( void );

#endif
/* --------------------- Works Cited -------------------- */
/* 
 * cschol. (2008). "Organization of C files: Answer."
 *      Stackoverflow.  Retrieved from https://stackoverflow
 *      .com/questions/47919/organization-of-c-files on 2022
 *      June 03.
 */
