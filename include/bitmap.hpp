#pragma once

#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdint.h>
#include <vector>

namespace IMAGE
{
    typedef struct BITMAP_HEADER
    {
        uint32_t filesize;
        uint32_t reserved;
        uint32_t dataoffset;

        uint32_t size;
        uint32_t width;
        uint32_t height;
        uint16_t planes;
        uint16_t bits_per_pixel;
        uint32_t compression;
        uint32_t imagesize;
        uint32_t y_pixels_per_m;
        uint32_t x_pixels_per_m;
        uint32_t colors_used;
        uint32_t important_colors;

        uint8_t signature[2]; // <-- this in theory need to go at the start, but for the padding this cause problems, see "https://github.com/adriabama06/image-to-ascii/tree/main/test/padding.c"
    } BITMAP_HEADER;

    typedef struct RGB
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } RGB;

    class BITMAP
    {
    public:
        BITMAP_HEADER header;
        std::vector<RGB> pixels;

        int decode(uint8_t* raw_data);
        std::vector<uint8_t> encode();

        int load(FILE* fp);
        int save(FILE* fp);
    };
} // namespace BITMAP

std::ostream& operator<<(std::ostream& os, const IMAGE::RGB& pixel);
std::ostream& operator<<(std::ostream& os, const IMAGE::BITMAP_HEADER& header);
