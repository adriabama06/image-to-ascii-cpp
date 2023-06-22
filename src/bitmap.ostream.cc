#include "include/bitmap.hpp"

std::ostream& operator<<(std::ostream& os, const IMAGE::RGB& pixel)
{
    os << "R: " << static_cast<int>(pixel.r) << ", G: " << static_cast<int>(pixel.g) << ", B: " << static_cast<int>(pixel.b);
    return os;
}

std::ostream& operator<<(std::ostream& os, const IMAGE::BITMAP_HEADER& header)
{
    os << "signature: " << std::string(reinterpret_cast<const char*>(header.signature), 2) << std::endl;

    os << "filesize: " << header.filesize << std::endl;
    os << "reserved: " << header.reserved << std::endl;
    os << "dataoffset: " << header.dataoffset << std::endl;

    os << "size: " << header.size << std::endl;
    os << "width: " << header.width << std::endl;
    os << "height: " << header.height << std::endl;
    os << "planes: " << header.planes << std::endl;
    os << "bits_per_pixel: " << header.bits_per_pixel << std::endl;
    os << "compression: " << header.compression << std::endl;
    os << "imagesize: " << header.imagesize << std::endl;
    os << "y_pixels_per_m: " << header.y_pixels_per_m << std::endl;
    os << "x_pixels_per_m: " << header.x_pixels_per_m << std::endl;
    os << "colors_used: " << header.colors_used << std::endl;
    os << "important_colors: " << header.important_colors;

    return os;
}