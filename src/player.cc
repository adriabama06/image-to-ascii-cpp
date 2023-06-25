#include "include/player.hpp"

#include "include/console.hpp"
#include "include/image.hpp"

#include <iostream>
#include <cstdio>
#include <csignal>
#include <fstream>
#include <chrono>

void exit_handler(int num) {
    CONSOLE::show_cursor();

    std::cout << std::endl;

    exit(num);
}

using namespace std;
using namespace IMAGE;

// printf is faster than std::cout
#ifdef _WIN32
    #define custom_print(str) printf("%s\n", str.c_str())
    #define custom_print_ptr(str) printf("%s", str->c_str())
#else
    #define custom_print(str) printf("%s", str.c_str())
    #define custom_print_ptr(str) printf("%s", str->c_str())
#endif

void PLAYER::player(const vector<string>& frames, const uint32_t framerate_microseconds, const bool clear_console, const bool verbose)
{
    signal(SIGINT, exit_handler);
    CONSOLE::hide_cursor();

    const auto start = chrono::high_resolution_clock::now();
    auto current = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::microseconds>(current - start).count();

    const size_t frames_size = frames.size();
    bool first_check = false;
    size_t last_i = 0;
    size_t i = 0;

    while (i < frames_size - 1)
    {
        current = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::microseconds>(current - start).count();

        i = elapsed_time / framerate_microseconds;

        if(first_check == true)
        {
            if(i == last_i)
            {
                continue;
            }
        }
        else
        {
            first_check = true;
        }

        last_i = i;

        const string& frame = frames.at(i);

        if(clear_console)
        {
            CONSOLE::clear_console();
        }
        if(verbose)
        {
            cout << i << "/" << frames_size << " "
            << chrono::time_point_cast<chrono::microseconds>(current).time_since_epoch().count() << " - "
            << chrono::time_point_cast<chrono::microseconds>(start).time_since_epoch().count() << " = " << elapsed_time << endl;
        }

        custom_print(frame);
    }

    CONSOLE::show_cursor();

    cout << endl;
}


void PLAYER::player_realtime_convert(const vector<filesystem::directory_entry>& files, const uint32_t framerate_microseconds, const bool clear_console, const bool verbose, const string& charecter_palette)
{
    signal(SIGINT, exit_handler);
    CONSOLE::hide_cursor();

    const auto start = chrono::high_resolution_clock::now();
    auto current = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::microseconds>(current - start).count();

    const size_t files_size = files.size();
    bool first_check = false;
    size_t last_i = 0;
    size_t i = 0;

    while (i < files_size - 1)
    {
        current = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::microseconds>(current - start).count();

        i = elapsed_time / framerate_microseconds;

        if(first_check == true)
        {
            if(i == last_i)
            {
                continue;
            }
        }
        else
        {
            first_check = true;
        }

        last_i = i;

        const filesystem::directory_entry& file = files.at(i);

        string filePath = file.path().string();
        BITMAP bmp(filePath);

        unique_ptr<string> frame = bmp.ascii(charecter_palette);

        if(clear_console)
        {
            CONSOLE::clear_console();
        }
        if(verbose)
        {
            cout << i << "/" << files_size << " "
            << chrono::time_point_cast<chrono::microseconds>(current).time_since_epoch().count() << " - "
            << chrono::time_point_cast<chrono::microseconds>(start).time_since_epoch().count() << " = " << elapsed_time << endl;
        }

        custom_print_ptr(frame);
    }

    CONSOLE::show_cursor();

    cout << endl;
}