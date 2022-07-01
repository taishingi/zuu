#include "Installation.hpp"

using namespace Yubel;

const string Installation::INSTALLATION_DIRECTORY = "/tmp/oh";
const string Installation::RUN_CMAKE = "cmake . && make";
const string Installation::TEMPORY_DIRECTORY = "/tmp";

Installation *Installation::clean(Installation *(*f)(Installation *i))
{
    return f(this);
}
Installation::Installation(const string &description)
{
    cout << description.c_str() << endl;
}

Installation::Installation(const string &description, const string &repository, const string &install)
{
    cout << description.c_str() << endl;
    this->clone(repository.c_str())->cd(INSTALLATION_DIRECTORY)->shell(install.c_str());
}
Installation *Installation::clean()
{
    return this->rm(INSTALLATION_DIRECTORY);
}
Installation *Installation::cd(const string &directory)
{
    return this->shell(this->checkout.append(directory.c_str()).c_str());
}

Installation *Installation::shell(const string &command)
{
    FILE *c = popen(command.c_str(), "w");

    pclose(c);
    return this;
}

Installation *Installation::rm(const string &path)
{
    return this->shell(this->remove.append(path.c_str()).c_str());
}

Installation *Installation::clone(const string &url)
{
    return this->shell(this->git.append(url.c_str()).append(" ").append(INSTALLATION_DIRECTORY).c_str());
}

Installation *Installation::compile()
{
    return this->cd(INSTALLATION_DIRECTORY)->shell(Installation::RUN_CMAKE);
}

Installation *Installation::download(const string &url)
{
    return this->cd(INSTALLATION_DIRECTORY)->shell(this->curl.append(url.c_str()).c_str());
}
Installation *Installation::get(const string &url)
{
    return this->cd(INSTALLATION_DIRECTORY)->shell(this->wget.append(url.c_str()).c_str());
}
int Installation::response(Installation *(*f)(Installation *i))
{
    f(this);
    return 0;
}
int Installation::response()
{
    this->clean();
    return 0;
}