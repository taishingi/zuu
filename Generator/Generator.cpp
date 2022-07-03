#include "Generator.hpp"

using namespace Yubel;

Generator::Generator()
{
    this->html.append("<!DOCTYPE html><html><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/css/bootstrap.min.css\"></head><body class=\"container\"><table class=\"table\"><thead><tr><th>Explain</th><th>tests</th></tr></thead><tbody>");
}

Generator::~Generator()
{
    this->html.clear();
}

string Generator::generate()
{
    return this->html.append("</tbody></table></body></html>");
}

void Generator::create(const string &filename)
{
    ofstream File(filename.c_str());
    File << this->generate().c_str();
    File.close();
}
void Generator::add(const string &description, bool test)
{
    this->html
        .append("<tr><td>")
        .append(description)
        .append("</td")
        .append("<td>")
        .append(test ? "OK" : "FAIL")
        .append("</td></tr>");
}