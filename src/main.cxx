
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
void printAllDirsRecursive(const fs::path &current_path) {

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
void getAllDirs(const std::string &path, std::vector<Info> &dirs)
{
    if (!fs::exists(path))
        return;
    for (const auto &next : fs::recursive_directory_iterator(path))
    {
        dirs.push_back(Info{._depth = 0, ._file_name = next.path().filename().string(), ._is_dir = next.is_directory(), ._path = fs::absolute(next.path().lexically_normal()).string()});
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
    getAllDirsRecursive(argv[1], dirs, -1);
    // getAllDirs(argv[1], dirs);
    for (const auto &dir : dirs)
    {
        if (dir._is_dir)
        {
            fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::green), "Depth : {} ,Path : {}\nName : {}\n", dir._depth, dir._path, dir._file_name);
        }
        else
        {
            fmt::print(fmt::emphasis::faint | fmt::fg(fmt::color::white), "Depth : {}, Path : {}\nName : {}\n", dir._depth, dir._path, dir._file_name);
        }
    }
    return 0;
};
