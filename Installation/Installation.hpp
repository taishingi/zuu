#ifndef YUBEL_INSTALLATION
#define YUBEL_INSTALLATION

#include <iostream>
#include <string>
#include <filesystem>

namespace Yubel
{
    using namespace std;

    class Installation
    {

    public:
        /**
         *
         * @brief Construct a new Installation object
         *
         * @param description The installation description
         *
         */
        Installation(const string &description);

        ~Installation();

        /**
         *
         * @brief change of directory
         *
         * @param directory The directory name
         *
         * @return Installation*
         *
         */
        Installation *cd(const string &directory);

        /**
         *
         * @brief Execute a shell command
         *
         * @param command The command to execute
         *
         * @return Installation*
         *
         */
        Installation *shell(const string &command);

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
        Installation *clone(const string &url);
        /**
         *
         * @brief Download  with curl
         *
         * @param url The url to download
         *
         * return Installation*
         *
         */
        Installation *download(const string &url);

        /**
         *
         * @brief download with wget
         *
         * @param url The url to download
         *
         * @return Installation*
         *
         */
        Installation *get(const string &url);

        /**
         *
         * @brief Remove file or directory
         *
         * @param path The path to delete
         *
         * @return Installation*
         *
         **/
        Installation *rm(const string &path);

        /**
         *
         * @brief Run compilation
         *
         * @return Installation*
         *
         */
        Installation *compile();
    };
}
#endif
