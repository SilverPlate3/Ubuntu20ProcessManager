#include "Console.h"
#include "SortProcessManager.h"
#include "ProcDirectoryIterator.h"
#include <iomanip>
#include "ProcMeminfoFile.h"
#include "KillProcess.h"


void Console::GetOperation()
{
	PrintMainMenu();
	auto mainChoice = GetMainInput();

	if (mainChoice == 1)
		ShowRunningProcesses();

	else if (mainChoice == 2)
		SystemState();

	else
		TerminateProcess();

	std::cin.get();
}


void Console::PrintMainMenu()
{
	std::cout << "\n\n"
		<< "====================================  Process Manager  ====================================\n"
		<< "[1] Show running process\n"
		<< "[2] Show system state\n"
		<< "[3] Terminate process\n"
		<< "Your choice: ";
}

int Console::GetMainInput()
{
	while (true)
	{
		std::string input;
		std::cin >> input;

		if (input == "1" || input == "2" || input == "3")
		{
			ClearConsole();
			return std::stoi(input);
		}

		std::cout << "\nIllegal input. Try again: ";
	}
}

void Console::ShowRunningProcesses()
{
	PrintSortMenu();
	auto sortBy = InputToNumber();
	ProcDirectoryIterator procIterator;
	procIterator.FillProcessManager();
	SortProcessManager sortProcessManager{};
	auto sortedProcesses = sortProcessManager.Sort(sortBy);
	PrintRunningProcesses(sortedProcesses);
}

void Console::SystemState()
{
	ClearConsole();
	const std::string PROC_MEMINFO("/proc/meminfo");
	ProcMeminfoFile procMeminfoFile;
	procMeminfoFile.SetStats(PROC_MEMINFO);
	std::cout << procMeminfoFile.GetMemoryInfoSummary();
}

void Console::TerminateProcess()
{
	std::cout << "PID to kill: ";
	const auto pidToKill(InputToNumber());
	KillProcess killProcess(pidToKill);
	const auto message = killProcess.Kill();
	std::cout << message << std::endl;
}

void Console::ClearConsole()
{
	std::cout << "\033[2J\033[1;1H";
}

void Console::PrintSortMenu()
{
	std::cout << "How should the output be sorted\n"
		<< "[1] By PID\n"
		<< "[2] By PPID\n"
		<< "[3] By Number of threads\n"
		<< "[4] By Virtual memory\n"
		<< "[5] By RAM usage\n"
		<< "[6] By Process Path\n"
		<< "[7] By Process Cmdline\n"
		<< "[other] Unsorted\n"
		<< "Your choice:";
}

int Console::InputToNumber()
{
	std::string input;
	std::cin >> input;
	ClearConsole();

	char* strtolDelimiter{};
	auto number =  std::strtol(input.c_str(), &strtolDelimiter, 10);
	return static_cast<int>(number);
}

void Console::PrintRunningProcesses(const std::vector<std::pair<int, ProcessData>>& sortedProcesses)
{
	std::cout << std::left
		<< std::setw(8) << "PID"
		<< std::setw(8) << "PPID" 
		<< std::setw(50) << "Process"
		<< std::setw(50) << "Cmdline" 
		<< std::setw(12) << "VmSize"
		<< std::setw(12) << "RAM"
		<< std::setw(8) << "Threads"
		<< std::endl;

	for (const auto& process : sortedProcesses)
	{
		if(!process.second.processPath.empty())
		{
			std::cout << process.second << std::endl;
		}
	}
}