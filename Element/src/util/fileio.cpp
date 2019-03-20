#include "pch.h"
#include "fileio.h"
#include <sstream>
#include <fstream>

namespace elm { namespace utils
{
	bool ReadFileToString(const std::string& path, std::string& outString)
	{
		std::ifstream in;
		std::stringstream ss{};
		in.open(path);
		if (in)
		{
			ss << in.rdbuf();
			outString = ss.str();
			in.close();
			return true;
		}
		return false;
	}

	bool AppendStringToFile(const std::string& path, const std::string& str)
	{
		std::ofstream out;
		out.open(path, std::ofstream::app | std::ofstream::out);
		if (out)
		{
			out << str;
			out.close();
			return true;
		}
		return false;
	}

	bool AppendStringsToFile(const std::string& path, const std::string* pString, size_t nrStrings)
	{
		if (pString == nullptr)
		{
			return false;
		}

		std::ofstream out;
		out.open(path, std::fstream::app | std::fstream::out);
		if (out)
		{
			for (size_t i = 0; i < nrStrings; i++)
			{
				out << pString[i];
			}
			out.close();
			return true;
		}
		return false;
	}
}}