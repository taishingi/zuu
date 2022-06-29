#include <Unit.hpp>

using namespace Yubel;

int exit_success(void)
{
    return EXIT_SUCCESS;
}
int exit_failure()
{
    return EXIT_FAILURE;
}
int main(void)
{
    return (new Unit("Test the Unit Framework"))
        ->ok(true)
        ->ko(false)
        ->differents("a", "b")
        ->identicals("a", "a")
        ->exist("README.md")
        ->empty("")
        ->contains("Linux", "Os linux is super")
        ->finish("linux", "Linus develop linux")
        ->begin("Linux", "Linux is developed by Linus")
        ->exist("/usr/bin/git")
        ->success(exit_success)
        ->fail(exit_failure)
        ->code(EXIT_SUCCESS, exit_success)
        ->code(EXIT_FAILURE, exit_failure)
    ->end();
}