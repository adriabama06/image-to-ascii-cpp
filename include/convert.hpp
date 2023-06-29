#include <iostream>
#include <vector>
#include <filesystem>

namespace CONVERT
{
    int convert(const std::string& input, const std::filesystem::directory_entry& input_stats, const std::string& output, const std::string& charecter_pallete, const bool verbose);
    int convert_multiple(const std::vector<std::filesystem::directory_entry>& bmpFiles, const std::string& output, const std::string& charecter_pallete, const bool verbose, size_t from, size_t to);
} // namespace CONVERT
