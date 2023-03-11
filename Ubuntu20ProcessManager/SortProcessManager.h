#pragma once
#include "ProcessManager.h"

class SortProcessManager
{
	using ProcessEntry = std::pair<int, ProcessData>;
	using ProcessVector = std::vector<ProcessEntry>;
public:

	ProcessVector Sort(int option);
	
	private:
	
		ProcessVector SortByPredicate(bool (SortProcessManager::* predicate)(const ProcessEntry&, const ProcessEntry&));
		bool CompareByPid(const ProcessEntry& a, const ProcessEntry& b);
		bool CompareByPPid(const ProcessEntry& a, const ProcessEntry& b);
		bool CompareByThreads(const ProcessEntry& a, const ProcessEntry& b);
		bool CompareByVirtualMemory(const ProcessEntry& a, const ProcessEntry& b);
		bool CompareByRAM(const ProcessEntry& a, const ProcessEntry& b);
		bool CompareByProcessPath(const ProcessEntry& a, const ProcessEntry& b);
		bool CompareByCmdline(const ProcessEntry& a, const ProcessEntry& b);
};