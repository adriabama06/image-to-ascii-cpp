#include "include/arguments.hpp"
#include "include/image.hpp"
#include "include/algorithm.hpp"
#include "include/player.hpp"
#include "include/convert.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread>
#include <set>

namespace fs = std::filesystem;
using namespace std;
using namespace IMAGE;


int main(int argc, const char** argv)
{
    ARGUMENTS options = parseArguments(argc, argv);

    fs::directory_entry input_stats(options.input);

    if(input_stats.is_regular_file())
    {
        return CONVERT::convert(options.input, input_stats, options.output, options.pallete, options.verbose);
    }

    set<fs::directory_entry> inputFilesSet;

    for (const auto& entry : fs::directory_iterator(options.input))
    {
        if(entry.is_regular_file() && entry.path().has_extension())
        {
            if(options.txt && entry.path().extension().string() == string(".txt"))
            {
                inputFilesSet.insert(entry);
            }
            else if(entry.path().extension().string() == string(".bmp"))
            {
                inputFilesSet.insert(entry);
            }
        }
    }

    vector<fs::directory_entry> inputFiles(inputFilesSet.begin(), inputFilesSet.end());

    inputFilesSet.~set();

    if(inputFiles.size() == 0)
    {
        cout << "Input folder is empty, can't find any .bmp/.txt file" << endl;

        return 1;
    }

    if(options.output.size() > 0)
    {
        size_t bmpFiles_size = inputFiles.size();

        if(options.n_threads == 0)
        {
            CONVERT::convert_multiple(inputFiles, options.output, options.pallete, options.verbose, 0, bmpFiles_size);
        }
        else
        {
            vector<thread> threads;

            for (size_t i = 0; i < options.n_threads; i++)
            {
                size_t from = i * (bmpFiles_size / options.n_threads);
                size_t to = (i + 1) * (bmpFiles_size / options.n_threads);

                threads.push_back(
                    thread(CONVERT::convert_multiple, inputFiles, options.output, options.pallete, options.verbose, from, to)
                );
            }

            for(auto& t : threads)
            {
                t.join();
            }
        }

        return 0;
    }

    if (options.preload)
    {
        vector<string> frames;

        for (const auto& entry : inputFiles)
        {
            const string filePath = entry.path().string();

            if(!options.txt)
            {
                BITMAP bmp;

                bmp.load(filePath);

                unique_ptr<string> ascii = bmp.ascii(options.pallete);

                frames.push_back(*ascii);
            }
            else
            {
                ifstream input(filePath);

                if (!input)
                {
                    exit(1);
                }

                string str;

                input.seekg(0, ios::end);
                str.reserve(input.tellg());
                input.seekg(0, ios::beg);

                str.assign((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());

                frames.push_back(move(str));

                input.close();
            }
        }

        PLAYER::player(frames, fps_microseconds(options.fps), !options.no_clear_console, options.verbose);
    }
    else
    {
        PLAYER::player(inputFiles, fps_microseconds(options.fps), options.pallete, !options.no_clear_console, options.verbose, options.txt);
    }

    return 0;
}