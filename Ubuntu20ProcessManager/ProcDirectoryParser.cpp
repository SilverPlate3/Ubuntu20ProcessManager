#include "ProcDirectoryParser.h"
#include "FilesystemIO.h"
#include <boost/format.hpp>
#include <filesystem>



std::string ProcDirectoryParser::GetExeContent(int pid)
{
	auto path = (boost::format("/proc/%1%/exe") % pid).str();
	if (!std::filesystem::exists(path))
		return "";

	std::error_code ec;
	auto content = std::filesystem::read_symlink(path, ec).string();
	return content;
}


std::string ProcDirectoryParser::GetCmdlineContent(int pid)
{
	auto path = (boost::format("/proc/%1%/cmdline") % pid).str();
	if (!std::filesystem::exists(path))
		return "";

	Utils::FileSystem::FilesystemIO filesystemIO;
	auto content = filesystemIO.ReadFileContent(path);
	return content;
}

ProcStatusFile ProcDirectoryParser::GetStatusContent(int pid)
{
	auto path = (boost::format("/proc/%1%/status") % pid).str();
	ProcStatusFile procStatusFile;
	procStatusFile.SetStats(path);
	return procStatusFile;
}




























