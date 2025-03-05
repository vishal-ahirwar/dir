
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
    int _depth{};
    std::string _file_name{};
    bool _is_dir{};
    std::string _path{};
};
void print(std::vector<Info> &dirs, bool bprint_fullpath)
{
    for (auto &dir : dirs)
    {
        std::string tabs{};
        while (dir._depth > 0)
        {
            tabs += "-----";
            dir._depth -= 1;
        }
        if (dir._is_dir)
        {
            fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::yellow), "{}{}\n", tabs, dir._file_name);
        }
        else
        {
            fmt::print(fmt::emphasis::faint | fmt::fg(fmt::color::ghost_white), "{}{}\n", tabs, dir._file_name);
        }
        if (bprint_fullpath)
        {
            fmt::print("{}{}\n", tabs, dir._path);  
        };
    }
};

void getAllDirsRecursive(const fs::path &current_path, std::vector<Info> &info, int depth = 0)
{
    ++depth;
    if (!fs::exists(current_path))
    {
        depth = 0;
        return;
    };
    for (const auto &next : fs::directory_iterator(current_path))
    {

        info.push_back(Info{._depth = depth, ._file_name = next.path().filename().string(), ._is_dir = next.is_directory(), ._path = fs::absolute(next.path().lexically_normal()).string()});

        if (next.is_directory())
        {
            getAllDirsRecursive(next.path(), info, depth);
        }
    }
};
void getAllDirs(const fs::path &path, std::vector<Info> &dirs)
{
    if (!fs::exists(path))
        return;
    for (const auto &next : fs::directory_iterator(path))
    {
        dirs.push_back(Info{._depth = 0, ._file_name = next.path().filename().string(), ._is_dir = next.is_directory(), ._path = fs::absolute(next.path().lexically_normal()).string()});
    };
};
int main(int argc, char *argv[])
{
    if (!(argc >= 2))
    {
        std::vector<Info> dirs{};
        getAllDirs(fs::current_path(), dirs);
        print(dirs, false);
        return 0;
    }
    if (argv[1] == std::string("-r"))
    {
        std::vector<Info> dirs{};
        getAllDirsRecursive(fs::current_path(), dirs, -1);
        print(dirs, false);
    }
    return 0;
};
