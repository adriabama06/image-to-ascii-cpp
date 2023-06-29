#pragma once

#include <iostream>
#include <memory>
#include <cstdint>
#include <vector>
#include <fstream>

namespace IMAGE
{
    const std::string DEFAULT_CHAR_PALETTE = " .,-~:=$#@";

    typedef struct RGB
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } RGB;

    std::unique_ptr<std::string> image2ascii(const std::vector<RGB>& pixels, const uint32_t& width, const uint32_t& height, const std::string& charecter_palette);
    std::unique_ptr<std::string> image2ascii(const std::vector<RGB>& pixels, const uint32_t& width, const uint32_t& height);

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

    class BITMAP
    {
    public:
        BITMAP() {}
        ~BITMAP() {}
        BITMAP(const std::string file) {
            this->load(file);
        }
        BITMAP(const std::string& file) {
            this->load(file);
        }

        BITMAP_HEADER header;
        std::vector<RGB> pixels;

        int decode(uint8_t* raw_data);
        std::vector<uint8_t> encode();

        int load(std::istream& input);
        int load(const std::string& file);

        int save(std::ostream& output);
        int save(const std::string& file);

        std::unique_ptr<std::string> ascii(const std::string& charecter_palette);
        std::unique_ptr<std::string> ascii();
    };
} // namespace BITMAP

std::ostream& operator<<(std::ostream& os, const IMAGE::RGB& pixel);
std::ostream& operator<<(std::ostream& os, const IMAGE::BITMAP_HEADER& header);
