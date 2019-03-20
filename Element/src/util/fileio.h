#pragma once

namespace elm { namespace utils
{
	bool ReadFileToString(const std::string& path, std::string& outString);
	bool AppendStringToFile(const std::string& path, const std::string& str);
	bool AppendStringsToFile(const std::string& path, const std::string* pString, size_t nrStrings);
}}