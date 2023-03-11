#include "KillProcess.h"
#include <signal.h>
#include <boost/format.hpp>

KillProcess::KillProcess(const int pid) :
	m_pid(pid) {}

std::string KillProcess::Kill()
{
	if (kill(m_pid, SIGABRT) != 0)
	{
		auto err = errno;
		return (boost::format("Couldn't kill PID: %1%  Kill returned error: %2%") % m_pid % err).str();
	}

	if (IsProcessDead())
	{
		return (boost::format("Successfully killed process:  %1%") % m_pid).str();
	}

	return (boost::format("Couldn't kill process:  %1%") % m_pid).str();
}

int KillProcess::IsProcessDead()
{
	return kill(m_pid, 0) != 0 ? false : true;
}