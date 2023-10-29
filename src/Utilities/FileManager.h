#pragma once

#include <fstream>
#include <ostream>
#include <vector>
#include <filesystem>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class FileManager
{
public:
    static std::string LoadFontFile(const std::string& fileName);
    static bool FileExists(const std::string& fileName);
    static std::vector<std::string> GetSaveFiles();

    static void SaveJson(json data, const std::string&  fileName);
    static json LoadJson(const std::string& fileName);

private:
    static std::string m_savePath;
    static std::string m_fontPath;
};