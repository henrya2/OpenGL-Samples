#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H

#include <string>
#include <unordered_map>

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
	~GLSLProgram();

	void deleteProgram();

	void compileShader(GLSLShaderType type, const std::string& source);
	void loadShader(GLSLShaderType type, const std::string& fileName);

	GLint getUniformLocation(const char* name);
	GLint getAttributeLocation(const char* name);

	void link();
	void use();
	void unUse();

	void setUniform(const char* name, const glm::vec2& v);
	void setUniform(const char* name, const glm::vec3& v);
	void setUniform(const char* name, const glm::vec4& v);
	void setUniform(const char* name, const glm::mat3& m);
	void setUniform(const char* name, const glm::mat4& m);
	void setUniform(const char* name, float val);
	void setUniform(const char* name, int val);
	void setUniform(const char* name, unsigned int val);
	void setUniform(const char* name, bool val);

private:
	GLuint mProgramId;
	bool mLinked;
	typedef std::unordered_map<std::string, GLuint> StringGLuintMap;
	StringGLuintMap mUniformLocations;
	StringGLuintMap mAttribLocations;
};

#endif