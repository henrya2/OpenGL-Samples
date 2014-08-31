#include "SamplesHelper.h"
#include "PathUtil.h"

namespace SamplesHelper
{
	void setupTheCurrentDirectoryToAssets()
	{
		std::string assetsPath = PathUtil::getExcutablePath();
		assetsPath += "/../../assets";
		PathUtil::setCurrentDirectory(assetsPath);
		std::string curDirPath = PathUtil::getCurrentDirectory();
	}
}
