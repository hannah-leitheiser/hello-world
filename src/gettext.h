/* Filename        : gettext.h
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : gettext translation boilerplate
 * ( Kernighan & Ritchie, 1988, p. 9: Comment Syntax ) */


#include <libintl.h> /* [ Fleury, 2016 ] */
#include <locale.h>  /* [ Fleury, 2016 ] */

#ifndef __GETTEXT_H /* [guard modeled on cschol, 2008] */
#define __GETTEXT_H

#define _(STRING) (const char*)gettext(STRING) 
   /* ( Fleury, 2016, Hello World! Example ) */ 

void LanguageLocalizationInit( void );

#endif

/* --------------------- Works Cited -------------------- */
/* 
 * Fleury, Emmanuel. (2016). "A Quick Gettext Tutorial."
 *      LaBRI.  Retrieved from https://www.labri.fr/perso/fl
 *      eury/posts/programming/a-quick-gettext-tutorial.html
 *      on 2022 December 28.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 * cschol. (2008). "Organization of C files: Answer."
 *      Stackoverflow.  Retrieved from https://stackoverflow
 *      .com/questions/47919/organization-of-c-files on 2022
 *      June 03.
 */
