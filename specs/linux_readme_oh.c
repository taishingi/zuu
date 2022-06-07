#include "../installation.h"

int main()
{
    return install("Get readme file")->download("https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/LICENSE.txt")->exist("LICENSE.txt")->run();
}