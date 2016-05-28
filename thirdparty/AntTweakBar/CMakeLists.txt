project(AntTweakBar CXX)

set(TARGET_LIB AntTweakBar)

SET(ANTTWEAKBAR_PUBLIC_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/AntTweakBar.h
)

file(GLOB ANTTWEAKBAR_SOURCE_C ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
set(ANTTWEAKBAR_SOURCE_NeedPreCompiledHeader 
	${CMAKE_CURRENT_SOURCE_DIR}/src/LoadOGL.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/LoadOGLCore.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TwBar.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TwColors.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TwFonts.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TwMgr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TwOpenGL.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TwOpenGLCore.cpp
)
set(ANTTWEAKBAR_SOURCE_NoPCHCpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/TwEventSFML.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/TwPrecomp.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/AntTweakBar.rc
)
file(GLOB ANTTWEAKBAR_SOURCE_H ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# Dependent include files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_definitions(-DTW_STATIC -DTW_NO_LIB_PRAGMA)

add_library(${TARGET_LIB} STATIC ${ANTTWEAKBAR_SOURCE_C} ${ANTTWEAKBAR_SOURCE_NeedPreCompiledHeader} ${ANTTWEAKBAR_SOURCE_NoPCHCpp} ${ANTTWEAKBAR_SOURCE_H} ${ANTTWEAKBAR_PUBLIC_HEADERS})

if(MSVC)
	#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /YuTwPrecomp.h /FITwPrecomp.h")
	set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/TwPrecomp.cpp
								PROPERTIES
								COMPILE_FLAGS "/YcTwPrecomp.h"
	)
	set_source_files_properties(${ANTTWEAKBAR_SOURCE_NeedPreCompiledHeader}
								PROPERTIES
								COMPILE_FLAGS "/YuTwPrecomp.h /FITwPrecomp.h"
	)
endif(MSVC)