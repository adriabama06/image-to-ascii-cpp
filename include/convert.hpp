#include <iostream>
#include <vector>
#include <filesystem>

namespace CONVERT
{
    void convert_multiple(const std::vector<std::filesystem::directory_entry>& bmpFiles, const std::string& output, const std::string& charecter_pallete, bool verbose, size_t from, size_t to);
} // namespace CONVERT
