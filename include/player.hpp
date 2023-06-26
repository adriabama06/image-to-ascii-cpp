#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#define fps_microseconds(fps) 1000000 / fps
#define cinema_microseconds(fps) 1001000 / fps

namespace PLAYER
{
    void player(const std::vector<std::string>& frames, const uint32_t framerate_microseconds, const bool clear_console, const bool verbose);
    void player(const std::vector<std::filesystem::directory_entry>& files, const uint32_t framerate_microseconds, const std::string& charecter_palette, const bool clear_console, const bool verbose, const bool txt);
} // namespace PLAYER
