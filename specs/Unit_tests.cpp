#include <Unit.hpp>

using namespace Yubel;

bool exit_bool(Unit *u)
{
    return false;
}
int exit_success(void)
{
    return EXIT_SUCCESS;
}
int exit_failure()
{
    return EXIT_FAILURE;
}

void application(Unit *u)
{
    u->ok(true)
        ->ko(false)
        ->differents("a", "b")
        ->identicals("a", "a")
        ->empty("")
        ->contains("Linux", "Os linux is super")
        ->finish("linux", "Linus develop linux")
        ->begin("Linux", "Linux is developed by Linus")
        ->success(exit_success)
        ->fail(exit_failure)
        ->theory("Theory is false", false, exit_bool)
        ->chaos("is false", exit_bool)
        ->code(EXIT_SUCCESS, exit_success)
        ->code(EXIT_FAILURE, exit_failure)
        ->end();
}

int main(void)
{
    (new Unit("Test the framework"))->infinite(application);
}