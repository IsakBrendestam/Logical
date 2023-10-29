#include "FileManager.h"

#include "Debug.h"

std::string FileManager::m_savePath = "res/saveFiles/";
std::string FileManager::m_fontPath = "res/fonts/";

bool FileManager::FileExists(const std::string&  fileName)
{
    std::ifstream f(fileName.c_str());
    return f.good();
}

std::string FileManager::LoadFontFile(const std::string&  fileName)
{
    std::string filePath = m_fontPath + fileName;
    if (!FileExists(filePath))
        return nullptr;

	std::string font;

    std::ifstream fileStream;
    fileStream.open(filePath);

    if (!fileStream.is_open())
    {
        return nullptr;
    }
	
    fileStream >> font;

	return font;
}

std::vector<std::string> FileManager::GetSaveFiles()
{
    std::vector<std::string> fileNames;
    for (const auto & entry : std::__fs::filesystem::directory_iterator(m_savePath))
    {
        std::string fileName = entry.path().filename();
        if (fileName.length() > 5)
            fileName.erase(fileName.end()-5, fileName.end());
        fileNames.push_back(fileName);
    }
    return fileNames;
}

void FileManager::SaveJson(json data, const std::string&  fileName)
{
    std::ofstream fileStream(m_savePath + fileName);

    fileStream << data.dump(4);
}

json FileManager::LoadJson(const std::string& fileName)
{
    std::ifstream fileStream(m_savePath+ fileName);
    json data;
    fileStream >> data;

    return data;
}