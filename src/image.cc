#include "include/image.hpp"

using namespace IMAGE;
using namespace std;

unique_ptr<string> IMAGE::image2ascii(const vector<RGB>& pixels, const uint32_t& width, const uint32_t& height, const string& charecter_palette)
{
    const size_t charecter_palette_length = charecter_palette.length();

    const uint32_t size = width * height;

    auto ascii = make_unique<string>();
    //auto ascii = unique_ptr<std::string>();

    ascii->reserve(size + height);

    uint32_t width_count = 0;

    for (uint32_t i = 0; i <= size - 1;)
    {
        width_count++;

        if (width_count <= width)
        {
            const RGB& pixel = pixels.at(i++);

            float avg = (pixel.r + pixel.g + pixel.b) / 3;

            float __color_select = (avg / 255.0f);

            uint8_t color_select = __color_select * charecter_palette_length;

            if(color_select >= charecter_palette_length) {
	            color_select = charecter_palette_length - 1;
            }

            ascii->push_back(charecter_palette.at(color_select));
        }
        else
        {
            ascii->push_back('\n');
            width_count = 0;
        }
    }

    ascii->push_back('\0');

    return ascii;
}

unique_ptr<string> IMAGE::image2ascii(const vector<RGB>& pixels, const uint32_t& width, const uint32_t& height)
{
    return IMAGE::image2ascii(pixels, width, height, DEFAULT_CHAR_PALETTE);
}
