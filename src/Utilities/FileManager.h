#pragma once

#include <fstream>
#include <ostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class FileManager
{
public:
    static std::string LoadFontFile(const std::string& fileName);
    static bool FileExists(const std::string& fileName);

    static void SaveJson(json data, const std::string&  fileName);
    static json LoadJson(const std::string& fileName);
};