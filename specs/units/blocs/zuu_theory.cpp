#include <unit.hpp>

using namespace Yubel;

namespace fs = std::filesystem;
bool filename_not_exist()
{	
	return fs::exists("dino");
}
bool filename_exist()
{
	return fs::exists(".");
}
int main()
{
	return (new Unit("Test the cc method"))
		->cc("Filename should not exist", false , filename_not_exist)->cc("Filename should be exist", true , filename_exist)->end();
}
