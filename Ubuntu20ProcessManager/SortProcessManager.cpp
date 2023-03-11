#include "SortProcessManager.h"

using ProcessEntry = std::pair<int, ProcessData>;
using ProcessVector = std::vector<ProcessEntry>;

ProcessVector SortProcessManager::Sort(int option)
{
	switch (option)
	{
	case(1): return SortByPredicate(&SortProcessManager::CompareByPid);
	case(2): return SortByPredicate(&SortProcessManager::CompareByPPid);
	case(3): return SortByPredicate(&SortProcessManager::CompareByThreads);
	case(4): return SortByPredicate(&SortProcessManager::CompareByVirtualMemory);
	case(5): return SortByPredicate(&SortProcessManager::CompareByRAM);
	case(6): return SortByPredicate(&SortProcessManager::CompareByProcessPath);
	case(7): return SortByPredicate(&SortProcessManager::CompareByCmdline);
	default:
		auto processes = ProcessManager::GetProcessMap();
		ProcessVector unsortedProcesses(processes.begin(), processes.end());
		return unsortedProcesses;
	}
}

ProcessVector SortProcessManager::SortByPredicate(bool (SortProcessManager::* predicate)(const ProcessEntry&, const ProcessEntry&))
{
	auto processes = ProcessManager::GetProcessMap();
	ProcessVector sortedProcesses(processes.begin(), processes.end());
	auto sortBy = std::bind(predicate, this, std::placeholders::_1, std::placeholders::_2);
	std::sort(sortedProcesses.begin(), sortedProcesses.end(), sortBy);
	return sortedProcesses;
}

bool SortProcessManager::CompareByPid(const ProcessEntry& a, const ProcessEntry& b)
{
	return a.second.pid < b.second.pid;
}

bool SortProcessManager::CompareByPPid(const ProcessEntry& a, const ProcessEntry& b)
{
	return a.second.ppid < b.second.ppid;
}

bool SortProcessManager::CompareByThreads(const ProcessEntry& a, const ProcessEntry& b)
{
	return a.second.threads < b.second.threads;
}

bool SortProcessManager::CompareByVirtualMemory(const ProcessEntry& a, const ProcessEntry& b)
{
	return a.second.virtualMemory < b.second.virtualMemory;
}

bool SortProcessManager::CompareByRAM(const ProcessEntry& a, const ProcessEntry& b)
{
	return a.second.RAM < b.second.RAM;
}

bool SortProcessManager::CompareByProcessPath(const ProcessEntry& a, const ProcessEntry& b)
{
	return a.second.processPath < b.second.processPath;
}

bool SortProcessManager::CompareByCmdline(const ProcessEntry& a, const ProcessEntry& b)
{
	return a.second.Commandline < b.second.Commandline;
}

