#pragma once
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

class ProcBaseFile
{
public:
	void SetStats(const std::string& path);

protected:

	std::string CleanStat(const std::string& stat);
	unsigned long long ConvertToNumber(const std::string& stat);
	void RunLambdaOnImportantFileLines(std::function<void(std::vector<std::string>)> lambda, const std::string& filePath);
	std::vector<std::string> SplitStringWithDelimitrer(const std::string& string, const std::string& delimiter);
	template <class T>
	bool IsVectorSizeCorrect(const std::vector<T> vector, long unsigned int size);
	unsigned long long ConvertToNumberOfBytes(const std::string& prefix);

public:
	std::unordered_map<std::string, unsigned long long> m_stats;
};