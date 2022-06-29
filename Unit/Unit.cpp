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
    return this->check(actual.compare("") != 0);
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
    cout << "Assertions : " << this->assertions << "Failure : " << this->failures << endl;
    return this->failures > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
