#include "include/bitmap.hpp"

#include <iostream>

using namespace std;
using namespace IMAGE;

int main(int argc, const char** argv)
{
    FILE* fp = fopen(argv[1], "rb");
    FILE* out_fp = fopen("out.bmp", "wb");

    if(fp == NULL)
    {
        cout << "Error opening file: " << argv[1] << endl;
        exit(1);
    }

    BITMAP bmp = BITMAP();

    bmp.load(fp);

    cout << bmp.pixels.at(0) << endl;

    cout << bmp.header << endl;

    bmp.save(out_fp);

    fclose(fp);
    fclose(out_fp);

    return 0;
}