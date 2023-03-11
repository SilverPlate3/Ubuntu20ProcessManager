#include "ProcDirectoryIterator.h"
#include "ProcessManager.h"
#include <filesystem>
#include <thread>


void ProcDirectoryIterator::FillProcessManager()
{
	ProcessManager::ClearProcessManager();
	SearchProcPids();
}

void ProcDirectoryIterator::SearchProcPids()
{
	const auto highestPid = GetHighestPID();

	std::vector<std::thread> threads;
	for(int i = 1; i <= highestPid; i++)
	{
		auto path = std::filesystem::path(PROC_DIRECTORY / std::to_string(i));

		if(!IsDirectoryExists(path))
		{
			continue;
		}

		threads.emplace_back([this, i] { AddProcess(i); });
		std::thread thread([this, i] { AddProcess(i); });
		if (thread.joinable())
		{
			thread.detach();
		}
	}

	for (auto& thread : threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

long long ProcDirectoryIterator::GetHighestPID()
{
	long highestPid = 0;
	for (const auto& entry : std::filesystem::directory_iterator(PROC_DIRECTORY))
	{
		char* strtollDelimiter{};
		const auto directoryName = entry.path().filename().c_str();
		auto pid = std::strtoll(directoryName, &strtollDelimiter, 10);

		if (pid > highestPid)
		{
			highestPid = pid;
		}
	}

	return highestPid;
}

bool ProcDirectoryIterator::IsDirectoryExists(const std::filesystem::path& path)
{
	if (!std::filesystem::exists(path))
	{
		return false;
	}

	if (!std::filesystem::is_directory(path))
	{
		return false;
	}

	return true;
}

void ProcDirectoryIterator::AddProcess(int pid)
{
	ProcessManager processManager;
	processManager.AddProcess(pid);
}
