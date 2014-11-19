#pragma once

#include <string>

namespace PathUtil
{
	void setCurrentDirectory(const std::string& path);
	std::string getCurrentDirectory();
	std::string getExcutablePath();
}
