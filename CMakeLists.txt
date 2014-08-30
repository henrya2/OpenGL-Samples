cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
cmake_policy(VERSION 2.8)

if(MSVC)
	set(BINARY_DIRECTORY build)
endif()

#########################################
# Add GLFW

set(GLFW_DIRECTORY glfw-3.0.4)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLFW_DIRECTORY}/include)

set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLFW_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLFW_DIRECTORY}/include)

##########################################
# Add GLM
set(GLM_DIRECTORY glm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/${GLM_DIRECTORY})

find_package(OpenGL REQUIRED)
set(GL_APP_LIBS ${OPENGL_gl_LIBRARY})
set(GL_APP_DEPS glfw)

function(createSample NAME)
	file(GLOB SAMPLE_SOURCE ${NAME}/*.cpp)
	file(GLOB SAMPLE_INLINE ${NAME}/*.inl)
	file(GLOB SAMPLE_HEADER ${NAME}/*.h)
	set(SAMPLE_NAME  ${NAME})

	add_executable(${SAMPLE_NAME} ${SAMPLE_SOURCE} ${SAMPLE_INLINE} ${SAMPLE_HEADER})
	target_link_libraries(${SAMPLE_NAME} ${GL_APP_LIBS} ${GL_APP_DEPS})
	add_dependencies(${SAMPLE_NAME} ${GL_APP_DEPS})
endfunction(createSample)

createSample(HelloGLFW)
createSample(HelloGLSL)