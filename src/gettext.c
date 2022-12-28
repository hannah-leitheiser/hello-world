/* Filename        : gettext.c
 * Type of File    : C Source Code
 * Date Created    : 2022JUN02
 * Author          : Hannah Leitheiser
 * Project Name    : Hello World
 * Description     : gettext translation boilerplate
 * ( Kernighan & Ritchie, 1988, p. 9: Comment Syntax ) */

#include <libintl.h> /* ( Fleury, 2016 ) */
#include <locale.h>  /* ( Fleury, 2016 ) */
#include <stdlib.h>
#include <stdio.h>
#include <config.h>

#include "hello_world.h"

#include "gettext.h"

void LanguageLocalizationInit( void ) {
  setlocale (LC_ALL, "");   
  bindtextdomain (PACKAGE, getenv("PWD"));
  textdomain (PACKAGE);
  /* Last three lines from question,
          ( hardboiled65, 2020 ) */

}

/* --------------------- Works Cited -------------------- */
/* 
 * Fleury, Emmanuel. (2016). "A Quick Gettext Tutorial."
 *      LaBRI.  Retrieved from https://www.labri.fr/perso/fl
 *      eury/posts/programming/a-quick-gettext-tutorial.html
 *      on 2022 December 28.
 * Kernighan, Brian W. & Ritchie, Dennis M.. (1988). "The C
 *      Programming Language, Second Edition." Prentise
 *      Hall.  ISBN 0-13-110370-9.
 * hardboiled65. (2020). "A simple gettext example is not
 *      working on linux." Stack Exchange.  Retrieved from h
 *      ttps://stackoverflow.com/questions/63918661/a-
 *      simple-gettext-example-is-not-working-on-linux on
 *      2022 December 28.
 */
