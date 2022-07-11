
#include "installation.hpp"

using namespace Yubel;


bool Yubel::app(const string &repository, const string &application, const string &command)
{
    make(application, "clear");
    string x;
    rm(application);
    clone(repository, application);
    make(application, x.append("cd /tmp/").append(application).append(" && ").append(command));
    return true;
}

/**
 *
 * @brief change of directory
 *
 * @param directory
 *
 * @return Installation*
 *
 */
void Yubel::cd(const string &directory)
{
    string x;
    make(directory, x.append("cd /tmp/").append(directory.c_str()));
    x.clear();
    x.assign(checkout);
}
/**
 *
 * @brief Enter in the installation directory
 *https://github.com/taishingi/yubel.git
 * @return Installation*
 *
 */
void Yubel::enter()
{
    cd(INSTALLATION_DIRECTORY);
}

/**
 *
 * @brief Execute a shell command
 *
 * @param command The command to execute
 *
 * @return Installation*
 *
 */
void Yubel::shell(const string &command)
{
    puts("\033[1;32m");
    FILE *c = popen(command.c_str(), "w");
    if (c == NULL)
    {
        pclose(c);
        exit(EXIT_FAILURE);
    }
    pclose(c);
}

/**
 *
 * @brief clone a remote repository
 *
 *
 * @param url the repo url
 *
 * @return Installation*
 *
 */
void Yubel::clone(const string &url, const string &directory)
{
    string log = "git log HEAD -1 --stat";
    string x = "git clone ";
    make(directory, x.append(url).append(" /tmp/").append(directory));
    x.assign("git clone ");
    cd(directory);
    make(directory,log);
}
/**
 *
 * @brief Remove file or directory
 *
 * @param path The path to delete
 *
 * @return void
 *
 **/
void Yubel::rm(const string &path)
{
    string x = "rm -rf /tmp/";
    make(path, x.append(path.c_str()));
    x.clear();
    x.assign("rm -rf /tmp/");
}

/**
 *
 * @brief Run compilation
 *
 * @return Installation*
 *
 */
void Yubel::compile()
{
    shell(RUN_CMAKE);
}

void Yubel::make(const string &application, const string &command)
{
    fprintf(stdout, "\n%s[ %s%s%s ]-[ %s%s%s ]\n", "\033[1;34m", "\033[1;36m", application.c_str(), "\033[1;34m", "\033[1;35m", command.c_str(), "\033[1;34m");
    this_thread::sleep_for(chrono::seconds(1));
    shell(command);
}
