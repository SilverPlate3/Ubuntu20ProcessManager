#include "ProcMeminfoFile.h"
#include <sstream>

ProcMeminfoFile::ProcMeminfoFile()
{
	m_stats = std::unordered_map<std::string, unsigned long long>{
		{MemTotal, 0},
		{MemAvailable, 0},
		{Active, 0},
		{SwapTotal, 0},
		{SwapFree, 0} };
}

std::string ProcMeminfoFile::GetMemoryInfoSummary()
{
	std::stringstream ss;
	ss
		<< "=========  Memory summary =========\n\n"
		<< "Total memory:  " << m_stats.at(MemTotal) << "\n"
		<< "Available memory:  " << m_stats.at(MemAvailable) << "\n"
		<< "Used memory:  " << m_stats.at(Active) << "\n"
		<< "Swap Total:  " << m_stats.at(SwapTotal) << "\n"
		<< "Swap Free:  " << m_stats.at(SwapFree) << std::endl;

	return ss.str();
}







