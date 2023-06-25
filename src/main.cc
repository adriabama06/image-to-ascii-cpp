#include "include/image.hpp"
#include "include/algorithm.hpp"
#include "include/player.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;
using namespace IMAGE;


int main(int argc, const char** argv)
{
    vector<fs::directory_entry> bmpFiles;

    std::string path(argv[1]);

    for (const auto& entry : fs::directory_iterator(path))
    {
        if(entry.path().has_extension() && entry.path().extension().string() == string(".bmp"))
        {
            bmpFiles.push_back(entry);
        }
    }
    
    CUSTOM_ALGORITHM::sort_by_aplhabet(bmpFiles);

    PLAYER::player_realtime_convert(bmpFiles, fps_ns(atof(argv[2])), true, true, DEFAULT_CHAR_PALETTE);

    return 0;
}












int old_main(int argc, const char** argv)
{
    vector<fs::directory_entry> bmpFiles;

    std::string path(argv[1]);

    for (const auto& entry : fs::directory_iterator(path))
    {
        if(entry.path().has_extension() && entry.path().extension().string() == string(".bmp"))
        {
            bmpFiles.push_back(entry);
        }
    }
    
    CUSTOM_ALGORITHM::sort_by_aplhabet(bmpFiles);

    vector<string> frames;

    for (const auto& entry : bmpFiles)
    {
        string file_path = entry.path().string();
        BITMAP bmp(file_path);
        unique_ptr<string> ascii = bmp.ascii();
    
        frames.push_back(*ascii);
    }

    PLAYER::player(frames, fps_ns(atof(argv[2])), true, true);

    return 0;
}
