#pragma once

#include <mutex>
#include "ProcDirectoryParser.h"
#include "ProcessData.h"


class ProcessManager
{
public:

	void AddProcess(int pid);

private:

	void SetProcessPath();
	void SetCommandLine();
	void SetStatsFromStatusFile();
	void CreateMissingMapEntry();

public:

	static void ClearProcessManager();
	static const std::unordered_map<int, ProcessData>& GetProcessMap();

private:

	static std::mutex m_mutex;
	static std::unordered_map<int, ProcessData> m_processes;
	ProcDirectoryParser m_procDirectoryParser;
	int m_pid;
};
