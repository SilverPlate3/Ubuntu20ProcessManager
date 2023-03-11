#pragma once
#include <iostream>


class KillProcess
{
public:
	KillProcess(const int pid);
	std::string Kill();
private:
	int IsProcessDead();
private:
	int m_pid;
};