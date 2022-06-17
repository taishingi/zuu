#ifndef YUBEL_LIBRARY_H
#define YUBEL_LIBRARY_H

#include <limits.h>
#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include "colors.h"

#define IS_OK "The actual value match true"
#define IS_KO "The actual value match false"
#define IS_EQUALS "The numbers are equals"
#define IS_NOT_EQUALS "The numbers are not equals"
#define IS_BEETWEEN   "The numbers are beetween min and max"
#define IS_NOT_BEETWEEN "The numbers are not beetween expected value"
#define IS_IDENTICAL "The strings are identical"
#define IS_NOT_IDENTICAL "The strings are different"
#define THEORY_IS_TRUE "The theory is true"
#define THEORY_IS_FALSE "The theory is false"
#define IS_DEF "The value has been defined successfully"
#define IS_NOT_DEF "The value has not been defined"
#define IS_EMPTY "The value is empty"
#define IS_NOT_EMPTY "The value is not empty"
#define IS_FULL "The value is at the maximum value"
#define IS_NOT_FULL "The value is not at the maximum value"
#define IS_NOT "The value is not equal to the expected value"
#define IS_NO_NOT "The value is equal to the expected value"
#define IS_IS "The value is equal to the expected value"
#define IS_NOT_IS "The value is not equal to the expected value"
#define PARADOX_IS_TRUE "The paradox is true"
#define PARADOX_IS_FALSE "The paradox is false"
#define IS_SUPERIOR "The value is superior to the expected value"
#define IS_NOT_SUPERIOR "The value is not superior to the expected value"
#define IS_INFERIOR "The value is inferior to the expected value"
#define IS_NOT_INFERIOR "The value is not inferior to the expected value"
#define IS_SUCCESSFUL "The exit status code is 0"
#define IS_NOT_SUCCESSFUL "The exit status code isn't 0"
#define IS_FAILED "The exit status code is 1"
#define IS_NOT_FAILED "The exit status code isn't 0"
#define CONTAINS "The actual value contains expected value"
#define NOT_CONTAINS "The actual value not contains the expected value"
#define SCENARIO_IS_TRUE "The scenario is true"
#define SCENARIO_IS_FALSE "The scenario is false"

extern void before_all(void);
extern void before(void);
extern void after(void);
extern void after_all(void);
extern bool policy;

typedef struct unit unit;
struct unit
{
    double assertions;
    double failures;
    int status;

    unit *(*scenario)(const char *description, unit *(*f)(unit *u));
    unit *(*theory)(const char *description, bool expected, bool (*f)(unit *u));
    unit *(*ok)(bool actual);
    unit *(*ko)(bool actual);
    unit *(*superior)(int expected, int actual);
    unit *(*inferior)(int expected, int actual);
    unit *(*beetween)(int actual, int min, int max);
    unit *(*check)(bool test, const char *s, const char *f);
    unit *(*equals)(int expected, int actual);
    unit *(*unequals)(int expected, int actual);
    unit *(*identical)(const char *expected, const char *actual);
    unit *(*different)(const char *expected, const char *actual);
    unit *(*contains)(const char *expected, const char *actual);
    unit *(*empty)(const char *actual);
    unit *(*full)(const char *actual);
    unit *(*def)(void *actual);
    unit *(*undef)(void *actual);
    unit *(*fail)(int (*actual)(void));
    unit *(*success)(int (*actual)(void));
    int (*immunity)(void);
};

unit *Unit(const char *description);

unit *beetween(int actual, int min, int max);


int immunity(void);
/**
 *
 * @brief  Check a scenario
 *
 * @param description The description
 * @param f                    The callback
 *
 * @return unit*
 *
 */
unit *scenario(const char *description, unit *(*f)(unit *u));

/**
 *
 * @brief Check a theory
 *
 * @param description       The theory description
 * @param expected           The theory expected result
 * @param f                          The theory callback
 *
 * @return unit*
 *
 **/
unit *theory(const char *description, bool expected, bool (*f)(unit *u));

/**
 *
 * @brief Check if a value is equal to true
 *
 * @param actual The value to check
 *
 * @return unit*
 *
 */
unit *ok(bool actual);

/**
 *
 * @brief Check if a value is equal to false
 *
 * @param actual The value to check
 *
 * @return unit*
 *
 */
unit *ko(bool actual);

/**
 *
 * @brief Check if a value is superior
 *
 * @param expected The expected value
 * @param actual  The actual value
 *
 * @return unit*
 *
 */
unit *superior(int expected, int actual);

/**
 *
 * @brief Check if a value is inferior
 *
 * @param expected The expected value
 * @param actual  The actual value
 *
 * @return unit*
 *
 */
unit *inferior(int expected, int actual);

/**
 *
 * @brief check if a value is between two numbers
 *
 * @param actual The value to check
 * @param min The minimal value
 * @param max The maximum value
 *
 * @return unit*
 *
 */
unit *beetween(int actual, int min, int max);

/**
 *
 * @brief execute an test
 *
 * @param test The tests to execute
 * @param successful The successfull message
 * @param failure The failure message
 *
 * @return unit*
 *
 */
unit *check(bool test, const char *s, const char *f);

/**
 *
 * @brief Check if two numbers are equals
 *
 * @param expected The expected value
 * @param actual The actual value
 *
 * @return unit*
 *
 **/
unit *equals(int expected, int actual);

/**
 *
 * @brief Check if two numbers are not equals
 *
 * @param expected The expected value
 * @param actual    The actual value
 *
 * @return unit*
 *
 */
unit *unequals(int expected, int actual);

/**
 *
 * @brief Check if two string are identical
 *
 * @param expected The expected value
 * @param actual    The actual value
 *
 * @return unit*
 *
 */
unit *identical(const char *expected, const char *actual);

/**
 *
 * @brief Check if two strings are differents
 *
 * @param expected The expected value
 * @param actual  The actual value
 *
 * @return unit*
 *
 */
unit *different(const char *expected, const char *actual);

/**
 *
 * @brief check if a string contains an another string
 *
 * @param expected The expected value
 * @param actual The actual value
 *
 * @return unit*
 *
 */
unit *contains(const char *expected, const char *actual);

/**
 *
 * @brief Check if a string is empty
 *
 * @param actual The value to check
 *
 * @return unit*
 *
 **/
unit *empty(const char *actual);

/**
 *
 * @brief Check if a string is full
 *
 * @param actual The value to check
 *
 * @return unit*
 */
unit *full(const char *actual);

/**
 *
 * @brief Check if a pointer has been defined
 *
 * @param p  The pointer to check
 *
 * @return unit*
 *
 */
unit *def(void *p);

/**
 *
 * @brief  Check if a pointer has been defined
 *
 * @param p
 * @return unit*
 */
unit *undef(void *p);

/**
 *
 * @brief Check the reponse status code is an EXIT_FAILURE code
 *
 * @param actual The status code to check
 *
 * @return unit*
 *
 */
unit *fail(int (*code)(void));

/**
 *
 * @brief Check if the response status code is an EXIT_SUCCESS code
 *
 * @param actual The status code to check
 *
 * @return unit*
 *
 */
unit *success(int (*code)(void));

#endif
