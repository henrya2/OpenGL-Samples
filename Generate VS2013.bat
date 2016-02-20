if not exist "build" (
	mkdir build
)

if not exist "build\debug" (
	mkdir build\debug
)

if not exist "build\release" (
	mkdir build\release
)

cd build
cmake -G "Visual Studio 12 2013" ..

pause