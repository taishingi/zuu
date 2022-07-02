#include <Installation.hpp>

using namespace Yubel;
void application()
{
    app("https://github.com/taishingi/yubel.git", "yubel");
    app("https://github.com/taishingi/nirvana.git", "nirvana", RUN_COMPOSER);
}

int main()
{
    infinite(application);
}