#include <string>
#include <vector>
#include <filesystem>

namespace CUSTOM_ALGORITHM
{
    void sort_by_aplhabet(std::vector<std::string>& arr);
    void sort_by_aplhabet(std::vector<std::filesystem::directory_entry>& arr);

    bool endsWith(std::string const &str, std::string const &suffix);
} // namespace CUSTOM_ALGORITHM
