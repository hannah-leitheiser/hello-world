#include <check.h> /* ( Malec, Archer, et. al., 2020 ) */
#include <stdlib.h>

#include "../src/word_wrap.h"

/* ck_assert_* functions and START_TEST and END_TEST
 * macros from ( Malec, Archer, et. al., 2020 ) 
 * chapter 4. */ 

START_TEST(word_wrap_hello) {
    const char* helloWorld="Hello, world!\n";
    char*       text;


    /* we don't know what that should be, except that it
     * should produce something at least as long as the
     * input text.  */
    text = wrapText( helloWorld, AUTODETECT, "", "");
    ck_assert_ptr_ne(text, NULL);
    ck_assert_int_ge( strlen(helloWorld), strlen(text));
    free(text);

    /* no wrap, no change */
    text = wrapText( helloWorld, NOWRAP, "", "");
    ck_assert_str_eq(helloWorld, text);
    free(text);

    text = wrapText( helloWorld, 1, "", "");
    ck_assert_str_eq(text, "H\n"
                           "e\n"
                           "l\n"
                           "l\n"
                           "o\n"
                           ",\n"
                           "\n"
                           "w\n"
                           "o\n"
                           "r\n"
                           "l\n"
                           "d\n"
                           "!\n");
    free(text);


    text = wrapText( helloWorld, 2, "", "");
    ck_assert_str_eq(text, "He\n"
                           "ll\n"
                           "o,\n"
                           "\n"
                           "wo\n"
                           "rl\n"
                           "d!\n");
    free(text);


    text = wrapText( helloWorld, 3, "", "");
    ck_assert_str_eq(text, "Hel\n"
                           "lo,\n"
                           "\n"
                           "wor\n"
                           "ld!\n");
    free(text);

    text = wrapText( helloWorld, 4, "", "");
    ck_assert_str_eq(text, "Hell\n"
                           "o,\n"
                           "\n"
                           "worl\n"
                           "d!\n");
    free(text);


    text = wrapText( helloWorld, 5, "", "");
    ck_assert_str_eq(text, "Hello\n"
                           ",\n"
                           "world\n"
                           "!\n");
    free(text);

    for(int i = 6 ; i < 14 ; i++) {
        text = wrapText( helloWorld, i, "", "");
        ck_assert_str_eq(text, "Hello,\n"
                               "world!\n");
        free(text);
    }

    /* Once there's sufficient space, the line should be
       unchanged. */

    for(int i = 14 ; i < 120 ; i++) {
        text = wrapText( helloWorld, i, "", "");
        ck_assert_str_eq(helloWorld, text);
        free(text);
    }


}
END_TEST


START_TEST(word_wrap_long) {
    const char* woods=
    "Whose woods these are I think I know.\n"
    "His house is in the village though;\n"
    "He will not see me stopping here\n"
    "To watch his woods fill up with snow.\n"
    "\n"
    "My little horse must think it queer\n"
    "To stop without a farmhouse near\n"
    "Between the woods and frozen lake\n"
    "The darkest evening of the year.\n"
    "\n"
    "He gives his harness bells a shake\n"
    "To ask if there is some mistake.\n"
    "The only other sound’s the sweep\n"
    "Of easy wind and downy flake.\n"
    "\n"
    "The woods are lovely, dark and deep,\n"
    "But I have promises to keep,\n"
    "And miles to go before I sleep,\n"
    "And miles to go before I sleep.\n";
                        /* (Frost, 1923) */

    char*       text;

    /* no wrap, no change */
    text = wrapText( woods, NOWRAP, "", "");
    ck_assert_str_eq(woods, text);
    free(text);


    /* no wrap, no change */
    text = wrapText( woods, 10, "", "");
    ck_assert_str_eq(text,  
         "Whose\n"
         "woods\n"
         "these are\n"
         "I think I\n"
         "know.\n"
         "His house\n"
         "is in the\n"
         "village\n"
         "though;\n"
         "He will\n"
         "not see\n"
         "me\n"
         "stopping\n"
         "here\n"
         "To watch\n"
         "his woods\n"
         "fill up\n"
         "with\n"
         "snow.\n"
         "\n"
         "My little\n"
         "horse\n"
         "must\n"
         "think it\n"
         "queer\n"
         "To stop\n"
         "without a\n"
         "farmhouse\n"
         "near\n"
         "Between\n"
         "the woods\n"
         "and\n"
         "frozen\n"
         "lake\n"
         "The\n"
         "darkest\n"
         "evening\n"
         "of the\n"
         "year.\n"
         "\n"
         "He gives\n"
         "his\n"
         "harness\n"
         "bells a\n"
         "shake\n"
         "To ask if\n"
         "there is\n"
         "some\n"
         "mistake.\n"
         "The only\n"
         "other\n"
         "sound’s\n"
         "the sweep\n"
         "Of easy\n"
         "wind and\n"
         "downy\n"
         "flake.\n"
         "\n"
         "The woods\n"
         "are\n"
         "lovely,\n"
         "dark and\n"
         "deep,\n"
         "But I\n"
         "have\n"
         "promises\n"
         "to keep,\n"
         "And miles\n"
         "to go\n"
         "before I\n"
         "sleep,\n"
         "And miles\n"
         "to go\n"
         "before I\n"
         "sleep.\n"
    );
    free(text);

}
END_TEST


START_TEST(word_wrap_indent) {
    const char* woods=
    "Whose woods these are I think I know.\n"
    "His house is in the village though;\n"
    "He will not see me stopping here\n"
    "To watch his woods fill up with snow.\n";
                        /* (Frost, 1923), excerpt */

    char*       text;

    /* no wrap, no change */
    text = wrapText( woods, NOWRAP, "", "");
    ck_assert_str_eq(woods, text);
    free(text);


    /* subsequent indent test */
    text = wrapText( woods, 10, "", "$$$$ ");
    ck_assert_str_eq(text,  
         "Whose\n"
         "$$$$ woods\n"
         "$$$$ these\n"
         "$$$$ are\n"
         "$$$$ I\n"
         "$$$$ think\n"
         "$$$$ I\n"
         "$$$$ know.\n"
         "$$$$ His\n"
         "$$$$ house\n"
         "$$$$ is\n"
         "$$$$ in\n"
         "$$$$ the\n"
         "$$$$ villa\n"
         "$$$$ ge\n"
         "$$$$ thoug\n"
         "$$$$ h;\n"
         "$$$$ He\n"
         "$$$$ will\n"
         "$$$$ not\n"
         "$$$$ see\n"
         "$$$$ me\n"
         "$$$$ stopp\n"
         "$$$$ ing\n"
         "$$$$ here\n"
         "$$$$ To\n"
         "$$$$ watch\n"
         "$$$$ his\n"
         "$$$$ woods\n"
         "$$$$ fill\n"
         "$$$$ up\n"
         "$$$$ with\n"
         "$$$$ snow.\n"
    );
    free(text);

    /* initial and subsequent indent test */
    text = wrapText( woods, 10, ">>>> ", "> ");
    ck_assert_str_eq(text,  
         ">>>> Whose\n"
         "> woods\n"
         "> these\n"
         "> are I\n"
         "> think I\n"
         "> know.\n"
         "> His\n"
         "> house\n"
         "> is in\n"
         "> the\n"
         "> village\n"
         "> though;\n"
         "> He will\n"
         "> not see\n"
         "> me\n"
         "> stopping\n"
         "> here\n"
         "> To\n"
         "> watch\n"
         "> his\n"
         "> woods\n"
         "> fill up\n"
         "> with\n"
         "> snow.\n"
    );
    free(text);

    /* subsequent indent only test */
    text = wrapText( woods, 10, "", ">> ");
    ck_assert_str_eq(text,  
         "Whose\n"
         ">> woods\n"
         ">> these\n"
         ">> are I\n"
         ">> think\n"
         ">> I\n"
         ">> know.\n"
         ">> His\n"
         ">> house\n"
         ">> is in\n"
         ">> the\n"
         ">> village\n"
         ">> though;\n"
         ">> He\n"
         ">> will\n"
         ">> not\n"
         ">> see me\n"
         ">> stoppin\n"
         ">> g here\n"
         ">> To\n"
         ">> watch\n"
         ">> his\n"
         ">> woods\n"
         ">> fill\n"
         ">> up\n"
         ">> with\n"
         ">> snow.\n"

    );
    free(text);


}
END_TEST


/* Modeled on "3.5 Creating a Suite" in 
 ( Malec, Archer, et. al., 2020 ) */

Suite * money_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Word Wrap");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, word_wrap_hello);
    tcase_add_test(tc_core, word_wrap_long);
    tcase_add_test(tc_core, word_wrap_indent);
    suite_add_tcase(s, tc_core);

    return s;
}

/* Modeled on "3.5 Creating a Suite" in 
 ( Malec, Archer, et. al., 2020 ) */

 int main(void)
 {
    int number_failed;
    Suite *s;
    SRunner *sr;
    s = money_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }

/* --------------------- Works Cited -------------------- */
/* 
 * Arien Malec, Branden Archer, Chris Pickett, Fredrik
 *      Hugosson, & Robert Lemmen. (2020 June 28.). "Check
 *      manual version 0.15.2." Libcheck.  Retrieved from ht
 *      tps://libcheck.github.io/check/doc/check_html/index.
 *      html on 2022 December 28.
 * Robert Frost. (1923.). ""Stopping by woods on a snowy
 *      evening" in New Hampshire, A Poem; with Notes and
 *      Grace Notes." Henry Holt & Company, NY.  Retrieved
 *      from https://www.gutenberg.org/files/58611/58611-
 *      h/58611-h.htm#ch25 on 2022 December 28.
 */
