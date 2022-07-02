#include <Installation.hpp>

using namespace Yubel;
int main()
{
    app("https://github.com/taishingi/yubel.git", "yubel");
    app("https://github.com/taishingi/nirvana.git", "nirvana", RUN_COMPOSER);
    return 0;
}