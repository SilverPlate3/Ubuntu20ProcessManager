#include "ProcessManager.h"
#include <thread>

std::mutex ProcessManager::m_mutex;
std::unordered_map<int, ProcessData> ProcessManager::m_processes;

void ProcessManager::AddProcess(int pid)
{
	m_pid = pid;
	std::vector<std::thread> threads;
	threads.emplace_back([this] { SetProcessPath(); });
	threads.emplace_back([this] { SetCommandLine(); });
	threads.emplace_back([this] { SetStatsFromStatusFile(); });

	for (auto& thread : threads)
	{
		if(thread.joinable())
		{
			thread.join();
		}
	}
}

void ProcessManager::SetProcessPath()
{
	const std::string actualBinaryPath = m_procDirectoryParser.GetExeContent(m_pid);
	std::unique_lock<std::mutex> lock(m_mutex);
	CreateMissingMapEntry();
	m_processes.at(m_pid).processPath = actualBinaryPath;
}

void ProcessManager::SetCommandLine()
{
	const auto cmdline = m_procDirectoryParser.GetCmdlineContent(m_pid);
	std::unique_lock<std::mutex> lock(m_mutex);
	CreateMissingMapEntry();
	m_processes.at(m_pid).Commandline = cmdline;
}

void ProcessManager::SetStatsFromStatusFile()
{
	const auto procStatusFile = m_procDirectoryParser.GetStatusContent(m_pid);
	std::unique_lock<std::mutex> lock(m_mutex);
	CreateMissingMapEntry();
	m_processes.at(m_pid).ppid = static_cast<int>(procStatusFile.m_stats.at(procStatusFile.PPID));
	m_processes.at(m_pid).virtualMemory = procStatusFile.m_stats.at(procStatusFile.VM_SIZE);
	m_processes.at(m_pid).RAM = procStatusFile.m_stats.at(procStatusFile.VM_RSS);
	m_processes.at(m_pid).threads = static_cast<int>(procStatusFile.m_stats.at(procStatusFile.THREADS));
}

void ProcessManager::CreateMissingMapEntry()
{
	if (m_processes.count(m_pid) == 0)
	{
		m_processes.emplace(m_pid, ProcessData());
		m_processes.at(m_pid).pid = m_pid;
	}
}

void ProcessManager::ClearProcessManager()
{
	m_processes.clear();
}

const std::unordered_map<int, ProcessData>& ProcessManager::GetProcessMap()
{
	return m_processes;
}
























