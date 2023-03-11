#pragma once
#include "ProcessData.h"
#include <vector>

class Console
{
public:
	void GetOperation();

private:
	void PrintMainMenu();
	int GetMainInput();
	void ShowRunningProcesses();
	void SystemState();
	void TerminateProcess();
	void ClearConsole();
	void PrintSortMenu();
	int InputToNumber();
	void PrintRunningProcesses(const std::vector<std::pair<int, ProcessData>>& sortedProcesses);
};