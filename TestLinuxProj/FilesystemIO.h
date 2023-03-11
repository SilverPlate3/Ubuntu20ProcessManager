#pragma once
#include <fstream>

namespace Utils
{
	namespace FileSystem
	{
		class FilesystemIO
		{
		public:
			std::string ReadFileContent(const std::string& path);
		};
	}
}
