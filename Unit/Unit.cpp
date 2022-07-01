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
    cout << "\033[1;34m" << endl;
    cout << description << endl;
    this->assertions = 0;
    this->failures = 0;
}

Unit *Unit::differents(const string &a, const string &b)
{
    return this->check(a.compare(b.c_str()) != 0);
}

Unit *Unit::identicals(const string &a, const string &b)
{
    return this->check(a.compare(b.c_str()) == 0);
}

Unit *Unit::exist(const string &filename)
{
    return this->check(filesystem::exists(filename.c_str()));
}

Unit *Unit::describe(const string &description, Unit *(*it)(Unit *u))
{
    cout << "\033[1;36m" << endl;
    cout << description << endl;
    return it(u);
}
Unit *Unit::ok(bool actual)
{
    return this->check(actual);
}

Unit *Unit::def(void *p)
{
    return this->check(p != nullptr);
}

Unit *Unit::empty(const string &actual)
{
    return this->check(actual.compare("") == 0);
}

Unit *Unit::ko(bool actual)
{
    return this->check(!actual);
}
Unit *Unit::success(int (*f)(void))
{
    return this->check(EXIT_SUCCESS == f());
}

Unit *Unit::fail(int (*f)(void))
{
    return this->check(EXIT_FAILURE == f());
}

Unit *Unit::begin(const string expected, const string &actual)
{
    return this->check(actual.rfind(expected.c_str(), 0) == 0);
}

Unit *Unit::finish(const string expected, const string &actual)
{
    return this->check(equal(expected.rbegin(), expected.rend(), actual.rbegin()));
}

Unit *Unit::code(int status, int (*code)(void))
{
    return this->check(status == code());
}

Unit *Unit::contains(const string expected, const string &actual)
{
    return this->check(actual.find(expected.c_str()));
}

Unit *Unit::check(bool tdd)
{
    tdd ? this->assertions++ : this->failures++;

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

        cout << "\033[1;37m] [ \033[1;32m" << this->assertions << " \033[1;31m" << this->failures << " \033[1;37m] "<< endl
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
    cout << "\033[1;32mAssertions " << this->assertions << " \033[1;37mFailures : \033[1;31m" << this->failures << " \033[1;36mExecuted :  \033[1;37m" << this->assertions + this->failures << endl;
    return this->failures > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
