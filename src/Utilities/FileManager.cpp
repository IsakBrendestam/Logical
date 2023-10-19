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