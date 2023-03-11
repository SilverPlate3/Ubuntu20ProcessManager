#pragma once

#include "ProcBaseFile.h"

class ProcStatusFile : public ProcBaseFile
{
public:
	const std::string PPID = "PPid";
	const std::string VM_SIZE = "VmSize";
	const std::string VM_RSS = "VmRSS";
	const std::string THREADS = "Threads";

public:
	ProcStatusFile();

};
