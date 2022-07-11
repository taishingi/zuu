#include <tux.hpp>

using namespace Yubel;

int run_pythagore()
{
	return hypot(3, 4);
}

int run_ha()
{

	for (int i = -4096; i < 4096; i++)
	{
		if (1 + i == 0)
		{
			return i;
		}
	}
	return 0;
}
int main()
{
	return (new Unit("Test the sure method"))
		->cc("the pythagore theorem should be correct", 5, run_pythagore)
		->cc("The x theorem sould be have only one solution", -1, run_ha)
		->end();
}
