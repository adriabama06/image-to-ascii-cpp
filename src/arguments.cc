#include "include/arguments.hpp"

#include "include/image.hpp"

#include <filesystem>
#include <cstring>

using namespace std;

const char* valid_arguments(size_t& i, size_t argc, const char** argv)
{
    if(i + 1 > argc)
    {
        cout << "Invalid arguments, check if arguments are ok" << endl;

        exit(0);
    }

    i++;

    return argv[i];
}

ARGUMENTS parseArguments(int argc, const char** argv)
{
    if(argc < 2)
    {
        cout << "Please run: " << argv[0] << " --help" << endl;
        exit(0);
    }

    ARGUMENTS options;

    for (size_t i = 0; i < argc; i++)
    {
        const char* param = argv[i];

        if(strcmp(param, "--help") == 0)
        {
            cout << argv[0] << " -i <input file/folder>" << endl;
            cout << "  --help                       (Optional) - Show this menu" << endl;
            cout << "  -i             <file/folder>            - Input file or folder, if the input is a folder you can use multithread or play, only supports bitmap (.bmp) format at 8bit per pixel and uncompressed" << endl;
            cout << "  -o             <file/folder> (Optional) - Output file or folder, optional if you just want to play it, if you play the input it will not save any file" << endl;
            cout << "  -fps           <number>                 - (Optional only if \"-o\" is not set) Set framerate in frames per second, example: 30, 24, 60, 23.976023976 (for cinema using float numbers use: \"1000 / (1001 / fps)\")" << endl;
            cout << "  -pallete       <string>      (Optional) - Set custom color pallete for ascii, the default is: \"" << IMAGE::DEFAULT_CHAR_PALETTE << "\"" << endl;
            cout << "  -no-clear-console            (Optional) - Prevent clear console everyframe, good for ssh connections" << endl;
            cout << "  -t             <number>      (Optional) - Threads for paralel frame conversion, sometimes can be slow than single thread, recomended on slow computers or if the folder has plenty of files" << endl;
            cout << "  -preload                     (Optional) - Set if preload the files in memory before play, if you no set this the playback will be converted in realtime" << endl;
            cout << "  -txt                         (Optional) - Set this to true if the input is a preconverted bmp file as txt" << endl;
            cout << "  -v                           (Optional) - Verbose output" << endl;

            exit(0);
        }

        if(strcmp(param, "-i") == 0)
        {
            const char* argument = valid_arguments(i, argc, argv);

            options.input = string(argument);

            continue;
        }

        if(strcmp(param, "-o") == 0)
        {
            const char* argument = valid_arguments(i, argc, argv);

            options.output = string(argument);

            continue;
        }

        if(strcmp(param, "-fps") == 0)
        {
            const char* argument = valid_arguments(i, argc, argv);

            options.fps = atof(argument);

            continue;
        }

        if(strcmp(param, "-pallete") == 0)
        {
            const char* argument = valid_arguments(i, argc, argv);

            options.pallete = string(argument);

            continue;
        }

        if(strcmp(param, "-no-clear-console") == 0)
        {
            options.no_clear_console = true;

            continue;
        }

        if(strcmp(param, "-t") == 0)
        {
            const char* argument = valid_arguments(i, argc, argv);

            options.n_threads = atoi(argument);

            continue;
        }

        if(strcmp(param, "-preload") == 0)
        {
            options.preload = true;

            continue;
        }

        if(strcmp(param, "-txt") == 0)
        {
            options.txt = true;

            continue;
        }

        if(strcmp(param, "-v") == 0)
        {
            options.verbose = true;

            continue;
        }
    }
    
    if(options.input.size() == 0)
    {
        cout << "The input (-i) is not optional" << endl;

        exit(0);
    }

    filesystem::directory_entry input_entry = filesystem::directory_entry(options.input);

    if(!input_entry.exists())
    {
        cout << options.input << " -> Not exists" << endl;

        input_entry.~directory_entry();

        exit(0);
    }

    if (options.output.size() == 0 && options.fps <= 0.0 && filesystem::directory_entry(options.input).is_directory())
    {
        cout << "If the output is not specified and input is a folder it means you will play it, please specify \"-fps\", fps can't be 0 or a negative number" << endl;

        input_entry.~directory_entry();

        exit(0);
    }

    if(options.output.size() > 0 && options.txt)
    {
        cout << "\"-txt\" is only for play not for convert" << endl;

        input_entry.~directory_entry();

        exit(0);
    }

    return options;
}