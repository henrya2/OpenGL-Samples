#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H

#include <string>
#include <map>

#include <gl/glew.h>
#include <glm/glm.hpp>

#include <stdexcept>

class GLSLProgramException : public std::runtime_error 
{
public:
	GLSLProgramException(const std::string& msg)
		: runtime_error(msg)
	{

	}
};

enum class GLSLShaderType
{
	VERTEX = GL_VERTEX_SHADER,
	FRAGMENT = GL_FRAGMENT_SHADER,
	GEOMETRY = GL_GEOMETRY_SHADER,
	TESS_CONTROL = GL_TESS_CONTROL_SHADER,
	TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
	COMPUTE = GL_COMPUTE_SHADER
};

class GLSLProgram
{
public:
	GLSLProgram();
};

#endif