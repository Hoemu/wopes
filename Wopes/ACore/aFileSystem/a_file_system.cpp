#include "a_file_system.h"

AFileSystem::AFileSystem(const string &targetPath) : filePath(targetPath) {}

void AFileSystem::setPath(const string &targetPath)
{
    this->filePath = targetPath;
}

void AFileSystem::createFilePath() {}

bool AFileSystem::isExist()
{
    path str(filePath);
    if (exists(str) == false)
    {
        std::cerr << "file open fail." << std::endl;
        return false;
    }
    return true;
}
