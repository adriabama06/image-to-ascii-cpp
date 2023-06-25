#include "include/convert.hpp"

#include "include/image.hpp"
#include "include/algorithm.hpp"

using namespace std;
using namespace IMAGE;
namespace fs = std::filesystem;

void CONVERT::convert_multiple(const std::vector<std::filesystem::directory_entry> &bmpFiles, const std::string &output, const std::string &charecter_pallete, bool verbose, size_t from, size_t to)
{
    fs::directory_entry output_stats(output);

    if (!output_stats.exists() && !output_stats.is_directory())
    {
        cout << "Output must a folder" << endl;

        exit(0);
    }

    for (size_t i = from; i < to; i++)
    {
        const auto &entry = bmpFiles.at(i);

        string path = entry.path().string();

        unique_ptr<string> ascii = BITMAP(path).ascii(charecter_pallete);

        string output_path = output_stats.path().string();

#ifdef _WIN32
        if (!CUSTOM_ALGORITHM::endsWith(output_path, "\\"))
        {
            output_path.push_back('\\');
        }
#else
        if (!CUSTOM_ALGORITHM::endsWith(output_path, "/"))
        {
            output_path.push_back('/');
        }
#endif

        output_path += entry.path().stem().string() + ".txt";

        ofstream output_file(output_path);

        if (!output_file)
        {
            cout << "Error opening output file" << endl;

            exit(0);
        }

        output_file << *ascii;

        if (!output_file.good())
        {
            cout << "Error writing output file" << endl;

            exit(0);
        }

        output_file.close();

        if(verbose)
        {
            cout << path << " -> " << output_path << endl;
        }
    }
}