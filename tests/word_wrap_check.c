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
    ck_assert_str_eq(text, text);
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
                    i          "world!\n");
        free(text);
    }

    /* Once there's sufficient space, the line should be
       unchanged. */

    for(int i = 14 ; i < 120 ; i++) {
        text = wrapText( helloWorld, i, "", "");
        ck_assert_str_eq(text, text);
        free(text);
    }


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
 */
