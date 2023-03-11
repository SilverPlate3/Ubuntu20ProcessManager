#pragma once
#include "ProcBaseFile.h"

class ProcMeminfoFile : public ProcBaseFile
{
public:
	ProcMeminfoFile();
	std::string GetMemoryInfoSummary();
private:
	const std::string MemTotal = "MemTotal";
	const std::string MemAvailable = "MemAvailable";
	const std::string Active = "Active";
	const std::string SwapTotal = "SwapTotal";
	const std::string SwapFree = "SwapFree";
};