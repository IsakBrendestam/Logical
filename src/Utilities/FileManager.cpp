#include "FileManager.h"

#include "Debug.h"

bool FileManager::FileExists(const std::string&  fileName)
{
    std::ifstream f(fileName.c_str());
    return f.good();
}

std::string FileManager::LoadFontFile(const std::string&  fileName)
{
    std::string filePath = "content/fonts/" + fileName;
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

void FileManager::SaveJson(json data, const std::string&  fileName)
{
    std::ofstream fileStream(fileName);

    fileStream << data.dump(4);
}

json FileManager::LoadJson(const std::string& fileName)
{
    std::ifstream fileStream(fileName);
    json data;
    fileStream >> data;

    return data;
}