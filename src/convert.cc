#include "include/convert.hpp"

#include "include/image.hpp"
#include "include/algorithm.hpp"

using namespace std;
using namespace IMAGE;
namespace fs = std::filesystem;

int CONVERT::convert(const string& input, const fs::directory_entry& input_stats, const string& output, const string& charecter_pallete, const bool verbose)
{
    if(!input_stats.path().has_extension() || input_stats.path().extension().string() != string(".bmp"))
        {
            cout << "Input must be a bmp file" << endl;

            return 1;
        }

        BITMAP bmp;

        bmp.load(input);

        unique_ptr<string> ascii = bmp.ascii(charecter_pallete);

        if(output.size() == 0)
        {
            cout << *ascii << endl;

            return 0;
        }

        fs::directory_entry output_stats(output);
        
        if(output_stats.exists() && output_stats.is_directory())
        {
            cout << "Output must be a file, not a folder" << endl;

            return 1;
        }

        ofstream output_file(output);

        if(!output_file)
        {
            cout << "Error opening output file" << endl;

            return 1;
        }

        output_file << *ascii;

        if(!output_file.good())
        {
            cout << "Error writing output file" << endl;

            return 1;
        }

        output_file.close();

        if(verbose)
        {
            cout << input << " -> " << output << endl;
        }

        return 0;
}

int CONVERT::convert_multiple(const std::vector<std::filesystem::directory_entry> &bmpFiles, const std::string &output, const std::string &charecter_pallete, const bool verbose, size_t from, size_t to)
{
    fs::directory_entry output_stats(output);

    if (!output_stats.exists() && !output_stats.is_directory())
    {
        cout << "Output must a folder" << endl;

        return 1;
    }

    for (size_t i = from; i < to; i++)
    {
        const auto &entry = bmpFiles.at(i);

        const string path = entry.path().string();

        BITMAP bmp;

        bmp.load(path);

        unique_ptr<string> ascii = bmp.ascii(charecter_pallete);

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

            return 1;
        }

        output_file << *ascii;

        if (!output_file.good())
        {
            cout << "Error writing output file" << endl;

            return 1;
        }

        output_file.close();

        if(verbose)
        {
            cout << path << " -> " << output_path << endl;
        }
    }

    return 0;
}