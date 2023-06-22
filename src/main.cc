#include "include/bitmap.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace IMAGE;

int main(int argc, const char** argv)
{
    ifstream input(argv[1], ios::binary);
    ofstream output("out.bmp", ios::binary);

    if (!input)
    {
        cout << "Error opening file: " << argv[1] << endl;
        exit(1);
    }

    BITMAP bmp;

    bmp.load(input);

    cout << bmp.pixels.at(0) << endl;
    cout << bmp.header << endl;

    bmp.save(output);

    return 0;
}