#include "../unit.h"

void before_all(void)
{
}

void before(void)
{
}

void after(void)
{
}

void after_all(void)
{
}

int secret()
{
	return 42;
}

void test_basic(void)
{
	ok(true);
	ko(false);
	equals(1, 1);
	equals(1, 1);
	equals(1, 1);
	equals(1, 1);
	equals(1, 1);
	equals(1, 1);
	equals(1, 1);
	paradox("pythagore incorrect", 3, hypot(3, 4));
	equals(1, 1);
	unequals(10, 1);
	identical("aa", "aa");
	different("a,", "a!");
	not(42, 46);
	is(42, 42);
}
int main(void)
{
	scenario("Basic tests", test_basic);
	theory("The secret of the life", 42, secret);
	def("aaa");
	full(100, 100);
	empty("");
	immunity();
	return status;
}
