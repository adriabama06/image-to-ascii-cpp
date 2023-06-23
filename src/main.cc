#include "include/image.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace IMAGE;

int main(int argc, const char** argv)
{
    string input = string(argv[1]);
    string output = string("out.bmp");

    if(argc >= 3)
    {
        output = string(argv[2]);
    }

    BITMAP bmp(input);

    cout << bmp.pixels.at(0) << endl;
    cout << bmp.header << endl;

    string df = string("@#$=:~-,. ");

    unique_ptr<string> as_ascii = bmp.ascii(df);

    cout << as_ascii->c_str() << endl;

    return 0;
}