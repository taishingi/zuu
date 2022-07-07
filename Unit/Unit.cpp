#ifndef __UNIT_H__
#define __UNIT_H__

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
    cout << "\033[1;37m[ \033[1;35m" << description << " \033[1;37m]" << endl
         << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    this->assertions = 0;
    this->failures = 0;
}

Unit *Unit::run(Unit *(*it)(Unit *u))
{
    return it(this);
}

Unit *Unit::theory(const string &describe, bool expected, bool (*f)(void))
{
    return this->check(describe, expected == f());
}

Unit *Unit::chaos(const string &describe, bool (*f)(void)){
    return this->check(describe, f() == false);
}

Unit *Unit::empty(const string &describe, const string &actual)
{
    return this->check(describe, actual.empty());
}
Unit *Unit::full(const string &describe, const string &actual)
{
    return this->check(describe, !actual.empty());
}

Unit *Unit::def(const string &describe, void *p)
{
    return this->check(describe, p != nullptr);
}

Unit *Unit::success(const string &describe, int (*f)(void))
{
    return this->check(describe, EXIT_SUCCESS == f());
}

Unit *Unit::fail(const string &describe, int (*f)(void))
{
    return this->check(describe, EXIT_FAILURE == f());
}

Unit *Unit::code(const string &describe, int status, int (*code)(void))
{
    return this->check(describe, status == code());
}

Unit *Unit::identicals(const string &describe, const string &a, const string &b)
{
    return this->check(describe, a.compare(b.c_str()) == 0);
}

Unit *Unit::differents(const string &describe, const string &a, const string &b)
{
    return this->check(describe, a.compare(b.c_str()) != 0);
}

Unit *Unit::ko(const string &describe, bool actual)
{
    return this->check(describe, !actual);
}

Unit *Unit::ok(const string &describe, bool actual)
{
    return this->check(describe, actual);
}

Unit *Unit::contains(const string &describe, const string &expected, const string &actual)
{
    return this->check(describe, actual.contains(expected));
}
Unit *Unit::check(const string &describe, bool tdd)
{
    tdd ? this->assertions++ : this->failures++;
    tdd ? cout << "\033[1;37m[ \033[1;32mOK \033[1;37m]\033[1;34m " << describe << endl
               << endl
        : cout << "\033[1;37m[\033[1;31m KO \033[1;37m]\033[1;34m " << describe << endl
               << endl;
    this_thread::sleep_for(chrono::milliseconds(50));
    return this;
}

Unit *Unit::cc(const string &describe, bool expected,bool (*f)(void), int repeat)	
{
    int i = 0;

    do
    {
        this->check(describe, expected == f());
        i++;
    } while (i < repeat);
    return this;
}
Unit *Unit::cc(const string &describe, int expected, int (*f)(void), int repeat)
{
    int i = 0;

    do
    {
        this->check(describe, expected == f());
        i++;
    } while (i < repeat);
    return this;
}
Unit *Unit::shure(const string &describe, int expected,int (*f)(void), int repeat)
{
    int i = 0;

    do
    {
        this->check(describe, expected == f());
        i++;
    } while (i < repeat);
    return this;
}
Unit *Unit::shure(const string &describe, bool expected, bool (*f)(void), int repeat)
{
    int i = 0;

    do
    {
        this->check(describe, expected == f());
        i++;
    } while (i < repeat);
    return this;
}
int Unit::end()
{
    double s = (this->assertions / (this->failures + this->assertions) * 100) / 4;
    double f = (this->failures / (this->failures + this->assertions) * 100) / 4;

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
    this_thread::sleep_for(chrono::seconds(7));
    return this->failures > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

#endif // __UNIT_H__
