#include "../unit.h"

int secret()
{
	return 42;
}

void test_basic(void)
{
	ok(true)
	ko(false)
	equals(1,1)
	unequals(1,2)
	identical("aa","aa")
	different("a,","a!")
	not(42,46)
	is(42,42)
}
int main(void)
{
	scenario("Basic tests",test_basic)
	theory("The secret of the life",42,secret)
	def("aaa")
	full(100,100)
	empty("")
	immunity()
	return status;
}

