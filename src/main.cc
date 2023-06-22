#include "include/image.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace IMAGE;

int main(int argc, const char** argv)
{
    string input = string(argv[1]);
    string output = string(argc >= 2 ? argv[2] : "out.bmp");

    BITMAP bmp(input);

    cout << bmp.pixels.at(0) << endl;
    cout << bmp.header << endl;

    bmp.save(output);

    return 0;
}