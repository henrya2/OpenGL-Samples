if not exist "build" (
	mkdir build
)

if not exist "build\debug" (
	mkdir build\debug
)

if not exist "build\release" (
	mkdir build\release
)

copy thirdparty\FreeImage-3.15.4\win32\FreeImage.dll build\debug\ /n
copy thirdparty\FreeImage-3.15.4\win32\FreeImage.dll build\release\ /n

cd build
cmake -G "Visual Studio 14 2015" ..

pause