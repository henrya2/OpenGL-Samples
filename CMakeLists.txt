cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

project(OpenGLSamples)

if(MSVC)
	set(BINARY_DIRECTORY build)
endif()


################################
# Add GLFW
set(GLFW_DIRECTORY glfw-3.0.3)
set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLFW_DIRECTORY})
set(GL_APP_DEPS glfw ${GLFW_LIBRARIES})
find_package(OpenGL REQUIRED)
set(GL_APP_LIBS ${OPENGL_gl_LIBRARY})


##########################################
# Add glew

set(GLEW_DIRECTORY glew-1.11.0)
set(GLEW_LIB_NAME libglew_static)

set(glew-cmake_BUILD_SHARED OFF CACHE STRING "" FORCE)
set(GLEW_ONLY_LIBS OFF CACHE STRING "" FORCE)
set(GLEW_INSTALL OFF CACHE STRING "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLEW_DIRECTORY})

list(APPEND GL_APP_DEPS ${GLEW_LIB_NAME})

##########################################
# Add GLM
set(GLM_DIRECTORY glm)

# Add the include_directories last, to avoid the headers files to polutes other libraries
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLM_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLFW_DIRECTORY}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLEW_DIRECTORY}/include)

################################
# Add freeimage

if(MSVC AND NOT CMAKE_CL_64)
	set(FREEIMAGE_BINARY_DIRECTORY "win32")
endif()
if(MSVC AND CMAKE_CL_64)
	set(FREEIMAGE_BINARY_DIRECTORY "win64")
endif()
if(APPLE)
	set(FREEIMAGE_BINARY_DIRECTORY "macosx")
endif()
if(UNIX AND NOT APPLE AND CMAKE_CL_64)
	set(FREEIMAGE_BINARY_DIRECTORY "linux64")
endif()
if(UNIX AND NOT APPLE AND NOT CMAKE_CL_64)
	set(FREEIMAGE_BINARY_DIRECTORY "linux64")
endif()

set(FREEIMAGE_DIRECTORY FreeImage-3.15.4)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${FREEIMAGE_DIRECTORY})

if(MSVC)
	set(FREEIMAGE_LIBRARY FreeImage.lib)
	set(FREEIMAGE_BINARY_FILE FreeImage.dll)
else()
	add_definitions(-DFREEIMAGE_LIB)
	set(FREEIMAGE_LIBRARY freeimage)
	set(FREEIMAGE_BINARY_FILE freeimage)
endif()
list(APPEND GL_APP_LIBS ${FREEIMAGE_LIBRARY})
set(FREEIMAGE_BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${FREEIMAGE_DIRECTORY}/${FREEIMAGE_BINARY_DIRECTORY}/${FREEIMAGE_BINARY_FILE})

if(WIN32)
	list(APPEND GL_APP_LIBS Winmm.lib)
endif()

##########################################
# Add framework
set(FRAMWORK_DIRECTORY framework)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${FRAMWORK_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${FRAMWORK_DIRECTORY})

set_property(TARGET framework PROPERTY COMPILE_DEFINITIONS GLEW_STATIC GLM_SWIZZLE GLM_FORCE_RADIANS)

list(APPEND GL_APP_DEPS framework)

set(Sample_DIRECTORY Samples)

function(createSample NAME)
	set(A_Sample_Path ${Sample_DIRECTORY}/${NAME})
	file(GLOB SAMPLE_SOURCE ${A_Sample_Path}/*.cpp)
	file(GLOB SAMPLE_INLINE ${A_Sample_Path}/*.inl)
	file(GLOB SAMPLE_HEADER ${A_Sample_Path}/*.h)
	set(SAMPLE_NAME  ${NAME})

	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${FREEIMAGE_DIRECTORY}/${FREEIMAGE_BINARY_DIRECTORY})

	add_executable(${SAMPLE_NAME} ${SAMPLE_SOURCE} ${SAMPLE_INLINE} ${SAMPLE_HEADER})
	target_link_libraries(${SAMPLE_NAME} ${GL_APP_LIBS} ${GL_APP_DEPS})
	add_dependencies(${SAMPLE_NAME} ${GL_APP_DEPS})

	set_property(TARGET ${SAMPLE_NAME} PROPERTY COMPILE_DEFINITIONS GLEW_STATIC GLM_SWIZZLE GLM_FORCE_RADIANS)
endfunction(createSample)

include("SamplesLists.txt")

foreach(varSample ${sampleLists})
	createSample(${varSample})
endforeach(varSample)