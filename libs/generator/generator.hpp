#ifndef YUBEL_GENERATOR
#define YUBEL_GENERATOR

#include <string>
#include <fstream>
namespace Yubel
{
    using namespace std;
    class Generator
    {
    private:
        string html;

    public:
        Generator();
        ~Generator();
        void create(const string &filename);
        void add(const string &description, bool test);
        string generate();
    };
}

#endif
