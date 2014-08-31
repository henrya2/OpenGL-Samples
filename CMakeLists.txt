cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

project(OpenGLSamples)

if(MSVC)
	set(BINARY_DIRECTORY build)
endif()

#########################################
# Add GLFW

set(GLFW_DIRECTORY glfw-3.0.4)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLFW_DIRECTORY}/include)

set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLFW_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLFW_DIRECTORY}/include)

find_package(OpenGL REQUIRED)
set(GL_APP_LIBS ${OPENGL_gl_LIBRARY})
set(GL_APP_DEPS glfw)

##########################################
# Add glew

set(GLEW_DIRECTORY glew-1.11.0)
set(GLEW_LIB_NAME libglew_static)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLEW_DIRECTORY}/include)

set(glew-cmake_BUILD_SHARED OFF CACHE STRING "" FORCE)
set(GLEW_ONLY_LIBS OFF CACHE STRING "" FORCE)
set(GLEW_INSTALL OFF CACHE STRING "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLEW_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLEW_DIRECTORY}/include)

list(APPEND GL_APP_DEPS ${GLEW_LIB_NAME})

##########################################
# Add GLM
set(GLM_DIRECTORY glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLM_DIRECTORY})

##########################################
# Add framework
set(FRAMWORK_DIRECTORY framework)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${FRAMWORK_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${FRAMWORK_DIRECTORY})

list(APPEND GL_APP_DEPS framework)

function(createSample NAME)
	file(GLOB SAMPLE_SOURCE ${NAME}/*.cpp)
	file(GLOB SAMPLE_INLINE ${NAME}/*.inl)
	file(GLOB SAMPLE_HEADER ${NAME}/*.h)
	set(SAMPLE_NAME  ${NAME})

	add_executable(${SAMPLE_NAME} ${SAMPLE_SOURCE} ${SAMPLE_INLINE} ${SAMPLE_HEADER})
	target_link_libraries(${SAMPLE_NAME} ${GL_APP_LIBS} ${GL_APP_DEPS})
	add_dependencies(${SAMPLE_NAME} ${GL_APP_DEPS})
endfunction(createSample)

createSample(HelloGLSL)