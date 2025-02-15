
// Auto Genrated C++ file by aura CLI
// None
#include <iostream>
#include <dirconfig.h>
#include <filesystem>
#include <vector>
#include <string>
#include <fmt/core.h>
#include <fmt/color.h>

namespace fs = std::filesystem;
struct Info
{
    bool _is_dir{};
    std::string _path{};
    std::string _file_name{};
};

void getAllDirs(const std::string &path, std::vector<Info> &dirs)
{
    if (!fs::exists(path))
        return;
    for (const auto &dir : fs::recursive_directory_iterator(path))
    {
        dirs.push_back(Info{._is_dir = dir.is_directory(), ._path = dir.path().string(), ._file_name = dir.path().filename().string()});
    };
};
int main(int argc, char *argv[])
{
    if (!(argc >= 2))
    {
        fmt::print(fmt::fg(fmt::color::rebecca_purple), "[error] : No path provided by user!\n");
        return 0;
    }
    std::vector<Info> dirs{};
    getAllDirs(argv[1], dirs);
    for (const auto &dir : dirs)
    {
        if (dir._is_dir)
        {
            fmt::print(fmt::emphasis::underline | fmt::fg(fmt::color::green), "Directory :\n\tPath : {},\n\tName : {}\n", dir._path, dir._file_name);
        }
        else
        {
            fmt::print(fmt::emphasis::faint | fmt::fg(fmt::color::white), "File :\n\tPath : {},\n\tName : {}\n", dir._path, dir._file_name);
        }
    }
    return 0;
};
