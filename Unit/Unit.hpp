#ifndef YUBEL_UNIT
#define YUBEL_UNIT

#include <iostream>
#include <string>
#include <filesystem>
#include <cmath>
#include <chrono>
#include <thread>
#include <cmath>

namespace Yubel
{
    using namespace std;
    class Unit
    {
    private:
        double assertions;
        double failures;
        Unit *check(const string &describe, bool tdd);

    public:
        /**
         *
         * @brief  Get stats
         *
         *
         * @return int
         */
        int end();

        /**
         *
         * @brief check if a function run successfully
         * @param describe  The decription
         * @param expected  The expected result
         * @param f         The callcack
         * @param repeat    The repeat function number
         *
         * @return true
         * @return false
         *
         */
        Unit *shure(const string &decribe, bool expected, bool (*f)(void), int repeat = 1);

        Unit *shure(const string &decribe, int expected, int (*f)(void), int repeat = 1);
        Unit *cc(const string &describe, int expected, int (*f)(void), int repeat = 1);

        Unit *cc(const string &describe, bool expected, bool (*f)(void), int repeat = 1);
        /**
         * @brief Construct a new Unit object
         *
         * @param description The description
         *
         */
        Unit(const string &description);

        /**
         * @brief Destroy the Unit object
         *
         */
        ~Unit();

        /**
         *
         * @brief Check a scenario
         *
         * @param description The ddescription of scenario
         * @param it The callback to call
         *
         * @return Unit*
         *
         */
        Unit *run(Unit *(*it)(Unit *u));

        /**
         *
         * @brief check if a theory is true
         *
         * @param describe The theory description
         * @param expected The expected value
         * @param f        The theory callback
         *
         * @return Unit*
         *
         **/
        Unit *theory(const string &describe, bool expected, bool (*f)(void));

        /**
         *
         * @brief Check if a theory is false
         *
         * @param describe The chaos description
         * @param f         The callback
         *
         * @return Unit*
         *
         */
        Unit *chaos(const string &describe, bool (*f)(void));

        /**
         *
         * @brief CHeck if the string is empty
         *
         * @param actual The string to check
         *
         * @return Unit*
         *
         */
        Unit *empty(const string &describe, const string &actual);
        Unit *full(const string &describe, const string &actual);

        /**
         *
         * @brief Check if a pointer has been defined
         *
         * @param p The pointer
         *
         * @return Unit*
         *
         */
        Unit *def(const string &describe, void *p);

        /**
         *
         * @brief Check if a callback return 0
         *
         * @param f The callback
         *
         * @return Unit*
         *
         */
        Unit *success(const string &describe, int (*f)(void));

        /**
         *
         * @brief Check if a callback return 1
         *
         * @param f The callback
         *
         * @return Unit*
         *
         */
        Unit *fail(const string &describe, int (*f)(void));

        /**
         *
         * @brief Check if a callback return correct status code
         *
         * @param status The expected status code
         * @param code The callback
         *
         * @return Unit*
         *
         */
        Unit *code(const string &describe, int status, int (*code)(void));

        /**
         *
         * @brief CHeck if two strings are idendicals
         *
         * @param a The first string
         * @param b The second string
         *
         * @return Unit*
         *
         */
        Unit *identicals(const string &describe, const string &a, const string &b);

        /**
         *
         * @brief CHeck if two string are differents
         *
         * @param a The first string
         * @param b The second string
         *
         * @return Unit*
         *
         **/
        Unit *differents(const string &describe, const string &a, const string &b);

        /**
         *
         * @brief check if a condition is true
         *
         * @param actual The value to check
         *
         * @return Unit*
         *
         */
        Unit *ok(const string &describe, bool actual);

        /**
         *
         * @brief check if a function return false
         *
         * @param actual the value to check
         *
         * @return Unit*
         *
         */
        Unit *ko(const string &describe, bool actual);

        /**
         *
         * @brief Check if a string contains an expected string
         *
         * @param expected The expected value
         * @param actual The actual value
         *
         * @return Unit*
         *
         */
        Unit *contains(const string &describe, const string &expected, const string &actual);

        void infinite(const string &describe, int (*f)(Unit *u));
    };
}

#endif
