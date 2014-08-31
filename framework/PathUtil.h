#ifndef PATH_UTIL_H
#define PATH_UTIL_H

#include <string>

namespace PathUtil
{
	void setCurrentDirectory(const std::string& path);
	std::string getCurrentDirectory();
	std::string getExcutablePath();
}

#endif