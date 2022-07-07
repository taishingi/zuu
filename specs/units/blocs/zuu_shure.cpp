#include <Unit.hpp>

using namespace Yubel;

bool run_pythagore()
{
	return hypot(3,4);
}
bool run_bad_pythagore()
{
	return 5 == hypot(3,5);
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
		
		->shure("the pythagore theorem should be correct",5 , run_pythagore)
		->shure("the pythagore theorem should bencorrect", false, run_bad_pythagore)
		->shure("The x theorem sould be have only one solution", -1, run_ha)
		->end();
}
