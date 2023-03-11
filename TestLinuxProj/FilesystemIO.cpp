#include "FilesystemIO.h"

std::string Utils::FileSystem::FilesystemIO::ReadFileContent(const std::string& path)
{
	std::fstream file{ path };
	if (!file)
		return "Couldn't get the file content";

	std::string fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();
	return fileContent;
}