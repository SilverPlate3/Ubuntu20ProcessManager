#include "ProcStatusFile.h"
#include <boost/algorithm/string.hpp>
#include "FilesystemIO.h"

ProcStatusFile::ProcStatusFile()
{
	m_stats = std::unordered_map<std::string, unsigned long long>{
		{PPID, 0},
		{VM_SIZE, 0},
		{VM_RSS, 0},
		{THREADS, 0}};
}
