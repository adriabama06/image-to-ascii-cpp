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

            return 1;
        }

        unique_ptr<string> ascii = BITMAP(options.input).ascii(options.pallete);

        if(options.output.size() == 0)
        {
            cout << *ascii << endl;

            return 1;
        }

        fs::directory_entry output_stats(options.output);
        
        if(output_stats.exists() && output_stats.is_directory())
        {
            cout << "Output must be a file, not a folder" << endl;

            return 1;
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

            return 1;
        }

        output_file.close();

        if(options.verbose)
        {
            cout << options.input << " -> " << options.output << endl;
        }

        return 0;
    }

    vector<fs::directory_entry> inputFiles;

    for (const auto& entry : fs::directory_iterator(options.input))
    {
        if(entry.is_regular_file() && entry.path().has_extension())
        {
            if(options.txt && entry.path().extension().string() == string(".txt"))
            {
                inputFiles.push_back(entry);
                
                continue;
            }

            if(entry.path().extension().string() == string(".bmp"))
            {
                inputFiles.push_back(entry);
            }
        }
    }

    if(inputFiles.size() == 0)
    {
        cout << "Input folder is empty, can't find any .bmp/.txt file" << endl;

        return 1;
    }

    if(options.output.size() > 0)
    {
        size_t bmpFiles_size = inputFiles.size();

        if(options.n_threads >= 1)
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
        else
        {
            CONVERT::convert_multiple(inputFiles, options.output, options.pallete, options.verbose, 0, bmpFiles_size);
        }

        return 0;
    }

    CUSTOM_ALGORITHM::sort_by_aplhabet(inputFiles);

    if (options.preload)
    {
        vector<string> frames;

        for (const auto& entry : inputFiles)
        {
            string filePath = entry.path().string();

            if(!options.txt)
            {
                BITMAP bmp(filePath);
                unique_ptr<string> ascii = bmp.ascii(options.pallete);

                frames.push_back(*ascii);

                continue;
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