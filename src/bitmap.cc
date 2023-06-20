#include "include/bitmap.hpp"

#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include <memory>

using namespace std;
using namespace IMAGE;

vector<RGB> flip_horizontally(vector<RGB> pixels, BITMAP_HEADER& header)
{
    auto flip_pixels = vector<RGB>();

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


    auto raw_data = unique_ptr<uint8_t[]>(new uint8_t[fp_size]);

    fread(raw_data.get(), sizeof(uint8_t), fp_size, fp);


    int err = this->decode(raw_data.get());

    if(err) {
        cout << "Error on decode" << endl;
    }

    return err;
}

unique_ptr<uint8_t[]> BITMAP::encode()
{
    auto raw_data = unique_ptr<uint8_t[]>(new uint8_t[header.dataoffset + header.imagesize]);

    memcpy(raw_data.get() + 2, &this->header, 52);
    memcpy(raw_data.get(), &this->header.signature, 2);

    if (header.dataoffset > 54)
    {
        memset(raw_data.get() + 54, (uint8_t) 0, header.dataoffset - 54);
    }

    uint32_t padding = header.width - ((header.width / 4) * 4);

    uint8_t* raw_pixels = raw_data.get() + header.dataoffset;

    uint32_t width_count = 0;
    uint32_t normal_count = 0;

    pixels = flip_horizontally(pixels, header);

    for (uint32_t i = 0; i < header.imagesize;)
    {
        width_count++;

        if(width_count <= header.width) // while is not the end of width, do this
        {
            RGB& pixel = pixels.at(normal_count++);

            raw_pixels[i++] = pixel.b;
            raw_pixels[i++] = pixel.g;
            raw_pixels[i++] = pixel.r;
        }
        else // in other case move i to skip padding and reset the width count
        {
            //i += padding;
            
            memset(raw_pixels + i, (uint8_t) 0, padding);

            // for (uint32_t j = i; j < i + padding; j++)
            // {
            //     raw_pixels[j] = (uint8_t) 0;
            // }
            
            i += padding;

            width_count = 0;
        }
    }

    return raw_data;
}

int BITMAP::save(FILE* fp)
{
    unique_ptr<uint8_t[]> raw_data = encode();
    uint32_t raw_data_size = header.dataoffset + header.imagesize;

    size_t wroted_bytes = fwrite(raw_data.get(), sizeof(uint8_t), raw_data_size, fp);

    if(wroted_bytes != raw_data_size)
    {
        return 1;
    }

    return 0;
}
