#include "ProcBaseFile.h"
#include <boost/algorithm/string.hpp>
#include "FilesystemIO.h"
#include <sstream>

void ProcBaseFile::SetStats(const std::string& path)
{
	auto lambda = [this](std::vector<std::string> lineParts) {
		if (m_stats.count(lineParts.front()))
		{
			auto statValue = CleanStat(lineParts.back());
			auto statValueRawNumber = ConvertToNumber(statValue);
			m_stats.at(lineParts.front()) = statValueRawNumber;
		}
	};

	RunLambdaOnImportantFileLines(lambda, path);
}

std::string ProcBaseFile::CleanStat(const std::string& stat)
{
	auto cleanStat = boost::trim_copy(stat);
	return cleanStat;
}

unsigned long long ProcBaseFile::ConvertToNumber(const std::string& stat)
{
	std::vector<std::string> stringParts = SplitStringWithDelimitrer(stat, " ");
	char* strtollDelimiter{};
	unsigned long long bytes = std::strtoll(stringParts.front().c_str(), &strtollDelimiter, 10);
	if (IsVectorSizeCorrect<std::string>(stringParts, 2))
		bytes *= ConvertToNumberOfBytes(stringParts.back());

	return bytes;
}

void ProcBaseFile::RunLambdaOnImportantFileLines(std::function<void(std::vector<std::string>)> lambda, const std::string& filePath)
{
	Utils::FileSystem::FilesystemIO filesystemIO;
	const auto fileContent = filesystemIO.ReadFileContent(filePath);

	std::istringstream fullTextStream(fileContent);
	std::string line;

	while (std::getline(fullTextStream, line))
	{
		std::vector<std::string> lineParts = SplitStringWithDelimitrer(line, ":");
		if (!IsVectorSizeCorrect<std::string>(lineParts, 2))
			continue;

		lambda(lineParts);
	}
}

std::vector<std::string> ProcBaseFile::SplitStringWithDelimitrer(const std::string& string, const std::string& delimiter)
{
	std::vector<std::string> stringParts;
	boost::split(stringParts, string, boost::is_any_of(delimiter));
	return stringParts;
}

template <class T>
bool ProcBaseFile::IsVectorSizeCorrect(const std::vector<T> vector, long unsigned int size)
{
	return vector.size() == size;
}

unsigned long long ProcBaseFile::ConvertToNumberOfBytes(const std::string& prefix)
{
	const auto B(1);
	const auto KB(1024);
	const auto MB(1048576);
	const auto GB(1073741824);
	const auto bytesPrefix = boost::trim_copy(boost::to_lower_copy(prefix));
	if (bytesPrefix == "b")
		return B;
	if (bytesPrefix == "kb")
		return KB;
	if (bytesPrefix == "mb")
		return MB;
	if (bytesPrefix == "gb")
		return GB;

	return 0;
}