#pragma once
#include <filesystem>
#include <vector>
#include <thread>

class ProcDirectoryIterator
{
public:
	void FillProcessManager();

private:
	void SearchProcPids();
	long long GetHighestPID();
	void AddProcess(int pid);
	bool IsDirectoryExists(const std::filesystem::path& path);
	void WaitForThreadsToEnd(std::vector<std::thread>& threads);

private:
	const std::filesystem::path PROC_DIRECTORY = "/proc";
};
