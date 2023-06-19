#include <iostream>

typedef struct RGB {
    int r;
    int g;
    int b;
} RGB;

std::ostream& operator<<(std::ostream& os, const RGB& pixel)
{
    os << "R: " << pixel.r << ", G: " << pixel.g << ", B: " << pixel.b;
    return os;
}

int main(int argc, const char** argv)
{
    RGB pixel;

    pixel.r = argc >= 2 ? atoi(argv[1]) : 255;
    pixel.g = argc >= 3 ? atoi(argv[2]) : 255;
    pixel.b = argc >= 4 ? atoi(argv[3]) : 255;

    std::cout << pixel << std::endl;

    return 0;
}