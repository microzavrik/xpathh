#pragma once

#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

namespace PathHandler
{
    extern ostream& os;
    extern istream& is;

    const fs::path PrintDirectoryContent(const fs::path& path);
    void DeleteFile(const fs::path& path);
    void CopyFile(const fs::path& source_path, const fs::path& target_path);
    void CreateFile(const fs::path& folder_path, const fs::path name_file);
    void Rename(const fs::path& old_path, const fs::path& new_path);
    void FileProperties(const fs::path& path);
}