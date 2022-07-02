#include "Unit.hpp"

using namespace Yubel;

Unit *u;

Unit::~Unit()
{
    this->assertions = 0;
    this->failures = 0;
}
Unit::Unit(const string &description)
{
    system("clear");
    cout << "\033[1;37m[ \033[1;35m" << description << " \033[1;37m]" << endl;
    this->assertions = 0;
    this->failures = 0;
}

Unit *Unit::theory(const string &describe, bool expected, bool (*f)(Unit *u))
{
    cout << "\033[1;37m[\033[1;35m " << describe << " \033[1;37m]\033[30m" << endl;
    return this->check(f(this) == expected, "The theory is true", "The theory is false");
}
Unit *Unit::chaos(const string &describe, bool (*f)(Unit *u))
{
    cout << "\033[1;37m[ \033[1;35m" << describe << " \033[1;37m]" << endl;

    return this->check(f(this) == false, "The chaos theory is true", "The chaos theroy is false");
}
Unit *Unit::differents(const string &a, const string &b)
{
    return this->check(a.compare(b.c_str()) != 0, "The strings are differents", "The strings are equals");
}

Unit *Unit::identicals(const string &a, const string &b)
{
    return this->check(a.compare(b.c_str()) == 0, "The strings are identicals", "The strings are differents");
}
Unit *Unit::describe(const string &description, Unit *(*it)(Unit *u))
{
    cout << "\033[1;37m[\033[ 1;34m" << description << "\033[1;37m ]" << endl;
    return it(u);
}
Unit *Unit::ok(bool actual)
{
    return this->check(actual, "The value is equal to true", "The value is equal to false");
}

Unit *Unit::def(void *p)
{
    return this->check(p != NULL, "The pointer has been defined", "The pointer has not been defined");
}

Unit *Unit::empty(const string &actual)
{
    return this->check(actual.compare("") == 0, "The string is empty", "The string is not empty");
}

Unit *Unit::ko(bool actual)
{
    return this->check(!actual, "The value match false", "The value match true");
}
Unit *Unit::success(int (*f)(void))
{
    return this->check(EXIT_SUCCESS == f(), "The status code is a success", "The status code is a failure");
}

Unit *Unit::fail(int (*f)(void))
{
    return this->check(EXIT_FAILURE == f(), "The status code is a failure", "The status code is a success");
}

Unit *Unit::begin(const string expected, const string &actual)
{
    return this->check(actual.rfind(expected.c_str(), 0) == 0, "The string start with the expected data", "The string don't start with the expected data");
}

Unit *Unit::finish(const string expected, const string &actual)
{
    return this->check(equal(expected.rbegin(), expected.rend(), actual.rbegin()), "The string finnish with the expected data", "The string don't finnish with the expected data");
}

Unit *Unit::code(int status, int (*code)(void))
{
    return this->check(status == code(), "The expected status code has been returned", "The function don't return the good status code");
}

Unit *Unit::contains(const string expected, const string &actual)
{
    return this->check(actual.find(expected.c_str()), "The string contains the expected string", "The expected string has not been found");
}

Unit *Unit::check(bool tdd, const string &s, const string &f)
{
    tdd ? this->assertions++ : this->failures++;
    tdd ? cout << "\033[1;37m[ \033[1;32mOK \033[1;37m]\033[1;34m " << s << endl : cout << "\033[1;37m[\033[1;31m KO \033[1;37m]\033[1;34m  " << f << endl;
    return this;
}

int Unit::end()
{
    double s = (this->assertions / (this->failures + this->assertions) * 100) / 2;
    double f = (this->failures / (this->failures + this->assertions) * 100) / 2;

    cout << endl
         << endl
         << "\033[1;37m[";
    if (this->failures == 0)
    {
        for (int i = 0; i < s; i++)
        {
            cout << "\033[1;32m*\033[30m";
        }

        cout << "\033[1;37m] [ \033[1;32m" << this->assertions << " \033[1;31m" << this->failures << " \033[1;37m] " << endl
             << endl
             << "[";
        for (int i = 0; i < s; i++)
        {
            cout << " ";
        }
    }
    else if (this->failures < this->assertions)
    {

        for (int i = 0; i < s; i++)
        {
            cout << "\033[1;32m*\033[30m";
        }

        cout << "\033[1;37m]" << endl
             << endl
             << "[";
        for (int i = 0; i < f - 1; i++)
        {
            cout << "\033[1;31m*\033[30m";
        }

        for (int i = f; i < s; i++)
        {

            cout << " ";
        }
    }
    else if (this->failures > this->assertions)
    {

        for (int i = 0; i < s; i++)
        {
            cout << "\033[1;32m*\033[30m";
        }

        for (int i = s; i < f - 1; i++)
        {

            cout << " ";
        }
        cout << "\033[1;37m]" << endl
             << endl
             << "[";
        for (int i = 0; i < f; i++)
        {
            cout << "\033[1;31m*\033[30m";
        }
    }
    else
    {
        for (int i = 0; i < s; i++)
        {
            cout << "\033[1;32m#\033[30m";
        }
        cout << "\033[1;37m]" << endl
             << endl
             << "[";
        for (int i = 0; i < f; i++)
        {
            cout << "\033[1;31m#\033[30m";
        }
    }
    cout << "\033[1;37m]\033[30m" << endl
         << endl;
    cout << "\033[1;32mAssertions " << this->assertions << " \033[1;37mFailures : \033[1;31m" << this->failures << " \033[1;36mExecuted :  \033[1;37m" << this->assertions + this->failures << endl
         << endl;
    return this->failures > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
