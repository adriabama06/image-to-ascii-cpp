#include "include/bitmap.hpp"

#include <iostream>

using namespace std;
using namespace IMAGE;

int main(int argc, const char** argv)
{
    FILE* fp = fopen(argv[1], "rb");

    if(fp == NULL)
    {
        cout << "Error opening file: " << argv[1] << endl;
        exit(1);
    }

    BITMAP bmp = BITMAP();

    bmp.load(fp);

    cout << bmp.pixels.at(0) << endl;

    fclose(fp);

    return 0;
}