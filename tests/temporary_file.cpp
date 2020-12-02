#include "temporary_file.hpp"
#include <filesystem>

TemporaryFile::TemporaryFile()
{
    auto directory = std::filesystem::temp_directory_path();
    std::filesystem::path filename = std::tmpnam(nullptr);
    auto file_path = directory / filename;
    fname = file_path.string();
}

TemporaryFile::~TemporaryFile()
{
    if (fs.is_open())
        fs.close();
    if (!fname.empty())
        std::filesystem::remove(fname);
}