#include "include/image.hpp"

#include <iostream>
#include <string>

typedef struct ARGUMENTS
{
    std::string input;
    std::string output;

    double fps = 0;
    std::string pallete = IMAGE::DEFAULT_CHAR_PALETTE;

    bool clear_console = false;
    bool verbose = false;

    size_t n_threads = 0;
} ARGUMENTS;

ARGUMENTS parseArguments(int argc, const char** argv);