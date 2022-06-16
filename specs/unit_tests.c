#include "../unit.h"

bool policy = true;

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

void test_success(void)
{
	successful(0)
	successful(EXIT_SUCCESS)
	fail(EXIT_FAILURE)
	fail(1)
}
void test_basic(void)
{
	ok(true)
	ko(false)
	equals(1, 1)
	equals(1, 1)
	equals(1, 1)
	equals(1, 1)
	equals(1, 1)
	equals(1, 1)
	equals(1, 1)
	paradox("pythagore incorrect", 3, hypot(3, 4))
	equals(1, 1)
	unequals(10, 1)
	identical("aa", "aa")
	different("a,", "a!")
	not(42, 46)
	contains("a","I am a man")
	is(42, 42);
}
int main(void)
{
	scenario("Basic tests", test_basic);
	scenario("Succesfull tests", test_success);
	theory("The secret of the life", 42, secret);
	def("aaa");
	full(100, 100);
	empty("");
	immunity();
	return status;
}
