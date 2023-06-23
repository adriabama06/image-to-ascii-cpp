#include "include/image.hpp"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <fstream>

using namespace std;
using namespace IMAGE;

vector<RGB> flip_horizontally(vector<RGB> pixels, const BITMAP_HEADER& header)
{
    vector<RGB> flip_pixels;
    flip_pixels.reserve(header.width * header.height);

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
    
    uint32_t padding = header.width - ((header.width / 4) * 4);

    uint8_t* raw_pixels = raw_data + header.dataoffset;

    uint32_t width_count = 0;

    pixels.reserve(header.width * header.height);

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

int BITMAP::load(std::istream& input)
{
    input.seekg(0, ios::end);

    uint32_t input_size = input.tellg();

    input.seekg(0, ios::beg); // go to the start of the file


    vector<uint8_t> raw_data(input_size);

    input.read(reinterpret_cast<char*>(raw_data.data()), input_size);


    int err = this->decode(raw_data.data());

    return err;
}

int BITMAP::load(std::string& file)
{
    ifstream input(file, ios::binary);

    if (!input)
    {
        return 1;
    }

    return this->load(input);
}

vector<uint8_t> BITMAP::encode()
{
    vector<uint8_t> raw_data(header.dataoffset + header.imagesize);

    memcpy(raw_data.data() + 2, &this->header, 52);
    memcpy(raw_data.data(), &this->header.signature, 2);

    if (header.dataoffset > 54)
    {
        memset(raw_data.data() + 54, (uint8_t) 0, header.dataoffset - 54);
    }

    uint32_t padding = header.width - ((header.width / 4) * 4);

    uint8_t* raw_pixels = raw_data.data() + header.dataoffset;

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

int BITMAP::save(std::ostream& output)
{
    vector<uint8_t> raw_data = encode();
    uint32_t raw_data_size = header.dataoffset + header.imagesize;

    output.write(reinterpret_cast<char*>(raw_data.data()), raw_data_size);

    if(!output.good())
    {
        return 1;
    }

    return 0;
}

int BITMAP::save(string& file)
{
    ofstream output(file, ios::binary);

    if (!output) {
        return 1;
    }

    return this->save(output);
}

std::unique_ptr<std::string> BITMAP::ascii(const std::string& charecter_palette)
{
    return IMAGE::image2ascii(this->pixels, this->header.width, this->header.height, charecter_palette);
}

unique_ptr<string> BITMAP::ascii()
{
    return IMAGE::image2ascii(this->pixels, this->header.width, this->header.height);
}