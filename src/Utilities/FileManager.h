#pragma once

#include <fstream>

class FileManager
{
public:
    static std::string LoadFontFile(const std::string& fileName);
    static bool FileExists(const std::string& fileName);
};