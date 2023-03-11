#pragma once
#include "ProcStatusFile.h"

class ProcDirectoryParser
{
public:
	std::string GetExeContent(int pid);
	std::string GetCmdlineContent(int pid);
	ProcStatusFile GetStatusContent(int pid);
};
