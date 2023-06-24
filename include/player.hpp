#include <iostream>
#include <string>
#include <vector>

#define fps_ns(fps) 1000000 / fps
#define cinema_fps_ns(fps) 1001000 / fps

namespace PLAYER
{
    void player(const std::vector<std::string>& frames, const uint32_t framerate_microseconds, const bool clear_console, const bool verbose);
    void player(const std::vector<std::string>& files, const uint32_t framerate_microseconds, const bool clear_console, const bool verbose, const std::string& charecter_palette);
} // namespace PLAYER
