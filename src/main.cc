#include "include/arguments.hpp"
#include "include/image.hpp"
#include "include/algorithm.hpp"
#include "include/player.hpp"
#include "include/convert.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>

namespace fs = std::filesystem;
using namespace std;
using namespace IMAGE;


int main(int argc, const char** argv)
{
    ARGUMENTS options = parseArguments(argc, argv);

    fs::directory_entry input_stats(options.input);

    if(input_stats.is_regular_file())
    {
        if(!input_stats.path().has_extension() || input_stats.path().extension().string() != string(".bmp"))
        {
            cout << "Input must be a bmp file" << endl;

            exit(0);
        }

        unique_ptr<string> ascii = BITMAP(options.input).ascii();

        if(options.output.size() == 0)
        {
            cout << *ascii << endl;

            exit(0);
        }

        fs::directory_entry output_stats(options.output);
        
        if(output_stats.exists() && output_stats.is_directory())
        {
            cout << "Output must be a file, not a folder" << endl;

            exit(0);
        }

        ofstream output_file(options.output);

        if(!output_file)
        {
            cout << "Error opening output file" << endl;

            exit(0);
        }

        output_file << *ascii;

        if(!output_file.good())
        {
            cout << "Error writing output file" << endl;

            exit(0);
        }

        output_file.close();

        if(options.verbose)
        {
            cout << options.input << " -> " << options.output << endl;
        }

        exit(0);
    }

    vector<fs::directory_entry> bmpFiles;

    for (const auto& entry : fs::directory_iterator(options.input))
    {
        if(entry.is_regular_file() && entry.path().has_extension() && entry.path().extension().string() == string(".bmp"))
        {
            bmpFiles.push_back(entry);
        }
    }

    if(options.output.size() > 0)
    {
        size_t bmpFiles_size = bmpFiles.size();

        if(options.n_threads >= 1)
        {
            vector<thread> threads;

            for (size_t i = 0; i < options.n_threads; i++)
            {
                size_t from = i * (bmpFiles_size / options.n_threads);
                size_t to = (i + 1) * (bmpFiles_size / options.n_threads);

                threads.push_back(
                    thread(CONVERT::convert_multiple, bmpFiles, options.output, options.pallete, options.verbose, from, to)
                );
            }

            for(auto& t : threads)
            {
                t.join();
            }

            exit(0);
        }
        else
        {
            CONVERT::convert_multiple(bmpFiles, options.output, options.pallete, options.verbose, 0, bmpFiles_size);
        
            exit(0);
        }
    }

    return 0;
}

int raltime_player_main(int argc, const char** argv)
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
