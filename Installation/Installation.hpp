#ifndef YUBEL_INSTALLATION
#define YUBEL_INSTALLATION

#include <iostream>
#include <string>
#include <filesystem>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>
namespace Yubel
{
    using namespace std;
    static const string DIRECTORY = "oh";
    static const string INSTALLATION_DIRECTORY = "/tmp/oh";
    static const string RUN_CMAKE = "cmake . && make";
    static const string TEMPORY_DIRECTORY = "/tmp";
    static const string RUN_COMPOSER = "composer install";
    static const string checkout = "cd ";
    static const string curl = "curl -fsSL";
    static const string wget = "wget ";
    static const string git = "git clone ";
    static const string rmdir = "rm -rf ";

    bool app(const string &repository, const string &app, const string &command = RUN_CMAKE);
    /**
     *
     * @brief change of directory
     *
     * @param directory The directory name
     *
     * @return Installation*
     *>
     */
    void cd(const string &directory);

    /**
     *
     * @brief Enter in the installation directory
     *
     * @return Installation*
     *
     */
    void enter();

    /**
     *
     * @brief Execute a shell command
     *
     * @param command The command to execute
     *
     * @return Installation*
     *
     */
    void shell(const string &command);

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
    void clone(const string &url, const string &directory);

    /**
     *
     * @brief Remove file or directory
     *
     * @param path The path to delete
     *"/tmp"
     * @return Installation*
     *
     **/
    void rm(const string &path);

    /**
     *
     * @brief Run compilat>ion
     *
     * @return void
     *
     */
    void compile();

    void make(const string &application, const string &command);
}

#endif
