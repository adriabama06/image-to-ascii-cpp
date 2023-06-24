#include "include/image.hpp"

using namespace IMAGE;
using namespace std;

string IMAGE::image2ascii(const vector<RGB>& pixels, const uint32_t& width, const uint32_t& height, const string& charecter_palette)
{
    const size_t charecter_palette_length = charecter_palette.length();

    const uint32_t size = width * height;

    string ascii;

    ascii.reserve(size + height);

    for (size_t i = 0; i < pixels.size() - 1;)
    {
        for (size_t width_count = 0; width_count < width; width_count++)
        {
            const RGB& pixel = pixels.at(i++);

            float avg = (pixel.r + pixel.g + pixel.b) / 3;

            float __color_select = (avg / 255.0f);

            uint8_t color_select = __color_select * charecter_palette_length;

            if(color_select >= charecter_palette_length) {
	            color_select = charecter_palette_length - 1;
            }

            ascii.push_back(charecter_palette.at(color_select));
        }
        
        ascii.push_back('\n');
    }

    return ascii;
}

string IMAGE::image2ascii(const vector<RGB>& pixels, const uint32_t& width, const uint32_t& height)
{
    return IMAGE::image2ascii(pixels, width, height, DEFAULT_CHAR_PALETTE);
}
