#pragma once
#include <string>

struct ProcessData
{
    int pid;
    int ppid;
	std::string processPath;
	std::string Commandline;
    unsigned long long virtualMemory;
    unsigned long long RAM;
    int threads;
};

std::ostream& operator<<(std::ostream& os, const ProcessData& processData);