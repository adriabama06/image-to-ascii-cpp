#include "include/algorithm.hpp"

using namespace std;

void CUSTOM_ALGORITHM::sort_by_aplhabet(vector<string> &arr)
{
    const size_t arr_size = arr.size();
    for (size_t i = 0; i < arr_size; i++)
    {
        for (size_t j = i + 1; j < arr_size; j++)
        {
            if (arr.at(i) > arr.at(j))
            {
                swap(arr.at(i), arr.at(j));
            }
        }
    }
}

void CUSTOM_ALGORITHM::sort_by_aplhabet(std::vector<std::filesystem::directory_entry>& arr)
{
    const size_t arr_size = arr.size();
    for (size_t i = 0; i < arr_size; i++)
    {
        for (size_t j = i + 1; j < arr_size; j++)
        {
            if (arr.at(i).path().filename().string() > arr.at(j).path().filename().string())
            {
                swap(arr.at(i), arr.at(j));
            }
        }
    }
}

bool CUSTOM_ALGORITHM::endsWith(std::string const &str, std::string const &suffix)
{
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}