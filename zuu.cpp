#include <iostream>
#include <string>
#include <filesystem>
#include <cassert>

using namespace std;
namespace fs = std::filesystem;

void installation()
{
    system("clear");
    string cmd = "g++ ";
    string path = "./specs/install";

    for (const auto &file : fs::recursive_directory_iterator(path.c_str()))
    {
        if (file.is_regular_file())
        {
            cmd.append(file.path()).append(" -l Installation -l tux -o yubel && ./yubel");
            FILE *c = popen(cmd.c_str(), "w");
            assert(c != nullptr);
            pclose(c);
            cmd.clear();
            cmd.assign(" g++ ");
        }
    }
}

void unit()
{
    system("clear");
    string cmd = "g++ ";
    string path = "./specs/units";

    for (const auto &file : fs::recursive_directory_iterator(path.c_str()))
    {
        if (file.is_regular_file())
        {
            cmd.append(file.path()).append(" -l Unit -o yubel -l tux && ./yubel");
            FILE *c = popen(cmd.c_str(), "w");
            assert(c != nullptr);
            pclose(c);
            cmd.clear();
            cmd.assign(" g++ ");
        }
    }
}

int ask()
{
    system("clear");
   fprintf(stdout, "\033[1;35mHi %s ! Please enter the number of the test\n\n", getenv("USER"));
    string choise;
    puts("\033[1;32m1)\033[1;36m Unit\n\033[1;32m2)\033[1;36m Installation\n\033[1;32m3)\033[1;36m Unit Loop\n\033[1;32m4)\033[1;36m Installation Loop\n\033[1;32m5)\033[1;36m All\n\033[1;32m6)\033[1;36m All loop\n\033[1;32m7)\033[1;36m Exit\n");
    cout << "\033[1;35mChoise : \033[1;32m";
    getline(cin, choise);
    if (
        choise.compare("1") == 0 ||
        choise.compare("2") == 0 ||
        choise.compare("3") == 0 ||
        choise.compare("4") == 0 ||
        choise.compare("5") == 0 ||
        choise.compare("6") == 0 ||
        choise.compare("7") == 0)
    {
        system("clear");
        return atoi(choise.c_str());
    }

    return ask();
}

int main(void)
{
    puts("\033[?25l\n");
    while (true)
    {
        int choise = ask();
        switch (choise)
        {
        case 1:
            unit();
            break;
        case 2:
            installation();
            break;

        case 3:
            do
            {
                unit();
            } while (true);
            break;
        case 4:
            do
            {
                installation();
            } while (true);
            break;
        case 5:
            unit();
            installation();
            break;
        case 6:
            do
            {
                unit();
                installation();
            } while (true);
            break;

        case 7:
            puts("\033[?25h");
            exit(EXIT_SUCCESS);
            break;

        default:
            continue;
            break;
        }
    }
    puts("\033[?25h");
    return 0;
}
