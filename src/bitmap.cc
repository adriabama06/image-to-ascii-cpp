#include "include/bitmap.hpp"

#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <memory>

using namespace std;
using namespace IMAGE;

std::ostream& operator<<(std::ostream& os, const IMAGE::RGB& pixel)
{
    os << "R: " << static_cast<int>(pixel.r) << ", G: " << static_cast<int>(pixel.g) << ", B: " << static_cast<int>(pixel.b);
    return os;
}

vector<RGB> flip_horizontally(vector<RGB> pixels, BITMAP_HEADER& header)
{
    vector<RGB> flip_pixels = vector<RGB>();

    for(int32_t row = header.height - 1; row >= 0; row--)
    {
        for(uint32_t col = 0; col < header.width; col++)
        {
            uint32_t pos = (row * header.width) + col;

            RGB& pixel = pixels.at(pos);
            
            flip_pixels.push_back(pixel);
        }
    }

    return flip_pixels;
}

int BITMAP::decode(uint8_t* raw_data)
{
    memcpy(&this->header, raw_data + 2, 52);
    memcpy(&this->header.signature, raw_data, 2);

    if(header.signature[0] != 'B' || header.signature[1] != 'M')
    {
        cout << "Invalid BitMap file" << endl;
        return 1;
    }
    
    cout << header.height << "x" << header.width << " - " << header.signature << endl;

    uint32_t padding = header.width - ((header.width / 4) * 4);

    uint8_t* raw_pixels = raw_data + header.dataoffset;

    uint32_t width_count = 0;

    for (uint32_t i = 0; i < header.imagesize;)
    {
        width_count++;

        if(width_count <= header.width) // while is not the end of width, do this
        {
            RGB pixel;

            pixel.b = raw_pixels[i++];
            pixel.g = raw_pixels[i++];
            pixel.r = raw_pixels[i++];

            pixels.push_back(pixel);
        }
        else // in other case move i to skip padding and reset the width count
        {
            i += padding;
            width_count = 0;
        }
    }

    pixels = flip_horizontally(pixels, this->header);

    return 0;
}

int BITMAP::load(FILE* fp)
{
    fseek(fp, 0, SEEK_END); // go to the end of the file

    uint32_t fp_size = ftell(fp);

    rewind(fp); // go to the start of the file


    unique_ptr<uint8_t[]> raw_data = unique_ptr<uint8_t[]>(new uint8_t[fp_size]);

    fread(raw_data.get(), sizeof(uint8_t), fp_size, fp);


    int err = this->decode(raw_data.get());

    if(err) {
        cout << "Error on decode" << endl;
    }

    return err;
}