#include "PathUtil.h"

#ifdef WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif // WIN32

namespace PathUtil
{
	void setCurrentDirectory(const std::string& path)
	{
#ifdef WIN32
		SetCurrentDirectoryA(path.c_str());
#else
		chdir(path.c_str());   
#endif // WIN32

	}

	std::string getCurrentDirectory()
	{
#ifdef WIN32
		char buff[MAX_PATH + 1];
		GetCurrentDirectory(MAX_PATH, buff);
		return buff;
#else
		char buff[PATH_MAX+1];
		getcwd(buff, PATH_MAX);
		return buff;
#endif
	}

	std::string getExcutablePath()
	{
#ifdef WIN32
		char buf[MAX_PATH + 1];
		HMODULE hHandle = GetModuleHandle(NULL);
		GetModuleFileNameA(hHandle, buf, MAX_PATH);

		const char pathSep = '\\';
#else
		char buf[PATH_MAX];
		readlink("/proc/self/exe", buf, PATH_MAX);

		const char pathSep = '/';
#endif

		std::string pathStr(buf);
		size_t index = pathStr.find_last_of(pathSep);
		return pathStr.substr(0, index);
	}

}