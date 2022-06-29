#include "Installation.hpp"

using namespace Yubel;

Installation::Installation(const string &description)
{
    cout << description.c_str() << endl;
}

Installation *Installation::cd(const string &directory)
{
    filesystem::current_path(filesystem::temp_directory_path());
    filesystem::current_path(directory.c_str());
    return this;
}

Installation *Installation::shell(const string &command)
{
    cout << "\033[32m";
    FILE *c = popen(command.c_str(), "w");

    if (!c)
    {
        pclose(c);
        exit(1);
    }
    pclose(c);
    cout << "\033[30m" << endl;
    return this;
}

Installation *Installation::rm(const string &path)
{
    filesystem::remove(path.c_str());
    return this;
}

Installation *Installation::clone(const string &url)
{
    string cmd = "git clone ";
    string end = filesystem::temp_directory_path().append("/").append("oh");
    cmd.append(url).append(end);
    return this->rm(end.c_str())->shell(cmd.c_str());
}

Installation *Installation::compile()
{
    return this->shell("cmake . && make");
}

Installation *Installation::download(const string &url)
{
    string cmd = "curl -fsSL ";
    cmd.append(url.c_str());
    return this->cd(filesystem::temp_directory_path())->shell(cmd.c_str());
}
Installation *Installation::get(const string &url)
{
    string cmd = "wget ";
    cmd.append(url.c_str());
    return this->cd(filesystem::temp_directory_path())->shell(cmd.c_str());
}