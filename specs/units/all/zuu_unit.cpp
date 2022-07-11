#include <unit.hpp>

using namespace Yubel;

bool exit_bool()
{
    return false;
}
bool exit_sure(void)
{
    return true;
}
int exit_success(void)
{
    return EXIT_SUCCESS;
}
int exit_failure()
{
    return EXIT_FAILURE;
}

Unit *application(Unit *u)
{
    u->shure("Exit must be return true",true, exit_sure, 5);
    for (int i = 0; i < 10; i++)
    {
        u->ok("Receveing or not data", true)
            ->ko("Data must not be receive", false)
            ->differents("Data must be differents", "a", "b")
            ->identicals("Data must be equals", "a", "a")
            ->empty("Data must be empty", "")
            ->contains("Data must be contains Linux", "linux", "Os linux is super")
            ->success("Data must be have a success return status code", exit_success)
            ->fail("Data must be have a failure return status code", exit_failure)
            ->theory("Theory must be return false", false, exit_bool)
            ->chaos("The chaos must be true", exit_bool)
            ->code("The status code must be equal to 0", 0, exit_success)
            ->code("The status code must be equal to 1", 1, exit_failure);
    }
    return u;
}

int main(void)
{
    return (new Unit("Test the framework"))->run(application)->end();
}
