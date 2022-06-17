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

int test_get_code()
{
	return EXIT_FAILURE;
}
int test_get_file()
{
	return EXIT_SUCCESS;
}
unit *test_basic(unit *u)
{
	u->ok(true)
		->ko(false)
		->equals(1, 1)
		->unequals(1, 2)
		->different("a", "aa")
		->identical("a", "a")
		->contains("Music", "Music is life")
		->empty("")
		->full("a")
		->success(test_get_file)
		->fail(test_get_code);
	return u;
}
int main(void)
{
	return Unit("Test")->scenario("Basic tests", test_basic)->immunity();
}
