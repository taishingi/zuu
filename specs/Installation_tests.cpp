#include <Installation.hpp>

using namespace Yubel;

int main()
{
    return (new Installation(
                "Check yubel installation",
                "https://github.com/taishingi/yubel"))
        ->response();
}