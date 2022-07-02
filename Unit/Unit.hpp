#ifndef YUBEL_UNIT
#define YUBEL_UNIT

#include <iostream>
#include <string>
#include <filesystem>
#include <cmath>
#include <chrono>
#include <thread>

namespace Yubel
{
    using namespace std;
    class Unit
    {
    private:
        double assertions;

        double failures;

        Unit *check(bool tdd, const string &s, const string &f);

    public:
        /**
         *
         * @brief  Get stats
         *
         * @return int
         *
         */
        int end();

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
        Unit *describe(const string &description, Unit *(*it)(Unit *u));

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
        Unit *theory(const string &describe, bool expected, bool (*f)(Unit *u));

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
        Unit *chaos(const string &describe, bool (*f)(Unit *u));

        /**
         *
         * @brief Check if the file exist
         *
         * @param filename The filename
         *
         * @return Unit*
         *
         */
        Unit *exist(const string &filename);

        /**
         *
         * @brief CHeck if the string is empty
         *
         * @param actual The string to check
         *
         * @return Unit*
         *
         */
        Unit *empty(const string &actual);

        /**
         *
         * @brief Check if a pointer has been defined
         *
         * @param p The pointer
         *
         * @return Unit*
         *
         */
        Unit *def(void *p);

        /**
         *
         * @brief Check if a callback return 0
         *
         * @param f The callback
         *
         * @return Unit*
         *
         */
        Unit *success(int (*f)(void));

        /**
         *
         * @brief Check if a callback return 1
         *
         * @param f The callback
         *
         * @return Unit*
         *
         */
        Unit *fail(int (*f)(void));

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
        Unit *code(int status, int (*code)(void));

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
        Unit *identicals(const string &a, const string &b);

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
        Unit *differents(const string &a, const string &b);

        /**
         *
         * @brief check if a condition is true
         *
         * @param actual The value to check
         *
         * @return Unit*
         *
         */
        Unit *ok(bool actual);

        /**
         *
         * @brief check if a function return false
         *
         * @param actual the value to check
         *
         * @return Unit*
         *
         */
        Unit *ko(bool actual);

        /**
         *
         * @brief  check if a string start with a string
         *
         * @param expected The expected start text
         * @param actual THe actual text
         *
         * @return Unit*
         *
         */
        Unit *begin(const string expected, const string &actual);

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
        Unit *contains(const string expected, const string &actual);

        /**
         *
         * @brief Check if a string finish with a string
         *
         * @param expected The expected value
         * @param actual The actual value
         * @return Unit*
         */
        Unit *finish(const string expected, const string &actual);

        void infinite(void (*f)(Unit *u));
    };
}

#endif
