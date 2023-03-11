#pragma once
#include <filesystem>

class ProcDirectoryIterator
{
public:
	void FillProcessManager();

private:
	void SearchProcPids();
	long long GetHighestPID();
	void AddProcess(int pid);
	bool IsDirectoryExists(const std::filesystem::path& path);

private:
	const std::filesystem::path PROC_DIRECTORY = "/proc";
};
