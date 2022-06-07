#include "../installation.h"

int main()
{
    return install("Test framework installation")->get("https://github.com/shingitai/yubel")->make("cmake . && make")->run();
}