#include "GLSLProgram.h"

#include <fstream>
#include <sstream>

GLSLProgram::GLSLProgram()
	: mProgramId(0)
	, mLinked(false)
{
	
}

GLSLProgram::~GLSLProgram()
{

}

void GLSLProgram::compileShader(GLSLShaderType type, const std::string& source)
{
	if (mProgramId == 0)
	{
		mProgramId = glCreateProgram();
	}

	GLuint shaderId = glCreateShader(static_cast<GLenum>(type));
	const char* cStr = source.c_str();
	glShaderSource(shaderId, 1, &cStr, NULL);

	glCompileShader(shaderId);

	// Check for errors
	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		// Compile failed, get log
		int length = 0;
		std::string logString;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) 
		{
			char * c_log = new char[length];
			int written = 0;
			glGetShaderInfoLog(shaderId, length, &written, c_log);
			logString = c_log;
			delete[] c_log;
		}
		std::string msg("Shader compilation failed.\n");
		msg += logString;
		throw GLSLProgramException(msg);
	}

	glAttachShader(mProgramId, shaderId);
}

void GLSLProgram::loadShader(GLSLShaderType type, const std::string& fileName)
{
	std::ifstream inFile(fileName, std::ios::in);
	if (!inFile)
	{
		std::string message = "Unable to open: " + fileName;
		throw GLSLProgramException(message);
	}

	// Get file contents
	std::stringstream sourceCode;
	sourceCode << inFile.rdbuf();
	inFile.close();

	try
	{
		compileShader(type, sourceCode.str());
	}
	catch (GLSLProgramException& e)
	{
		std::string message = fileName + std::string(": ") + e.what();
		throw GLSLProgramException(message);
	}
}

void GLSLProgram::link()
{
	glLinkProgram(mProgramId);
	mLinked = true;
}

void GLSLProgram::use()
{
	glUseProgram(mProgramId);
}

GLint GLSLProgram::getUniformLocation(const char* name)
{
	StringGLuintMap::iterator iter = mUniformLocations.find(name);

	if (iter == mUniformLocations.end())
	{
		GLint loc = glGetUniformLocation(mProgramId, name);
		mUniformLocations[name] = loc;

		return loc;
	}

	return iter->second;
}

GLint GLSLProgram::getAttributeLocation(const char* name)
{
	StringGLuintMap::iterator iter = mAttribLocations.find(name);

	if (iter == mAttribLocations.end())
	{
		GLint loc = glGetAttribLocation(mProgramId, name);
		mAttribLocations[name] = loc;

		return loc;
	}

	return iter->second;
}

void GLSLProgram::setUniform(const char* name, const glm::vec2& v)
{
	GLint loc = getUniformLocation(name);
	glUniform2fv(loc, 1, &v[0]);
}

void GLSLProgram::setUniform(const char* name, const glm::vec3& v)
{
	GLint loc = getUniformLocation(name);
	glUniform3fv(loc, 1, &v[0]);
}

void GLSLProgram::setUniform(const char* name, const glm::vec4& v)
{
	GLint loc = getUniformLocation(name);
	glUniform4fv(loc, 1, &v[0]);
}

void GLSLProgram::setUniform(const char* name, const glm::mat3& m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::setUniform(const char* name, const glm::mat4& m)
{
	GLint loc = getUniformLocation(name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

void GLSLProgram::setUniform(const char* name, float val)
{
	GLint loc = getUniformLocation(name);
	glUniform1f(loc, val);
}

void GLSLProgram::setUniform(const char* name, int val)
{
	GLint loc = getUniformLocation(name);
	glUniform1i(loc, val);
}

void GLSLProgram::setUniform(const char* name, unsigned int val)
{
	GLint loc = getUniformLocation(name);
	glUniform1ui(loc, val);
}

void GLSLProgram::setUniform(const char* name, bool val)
{
	GLint loc = getUniformLocation(name);
	glUniform1i(loc, val);
}

void GLSLProgram::deleteProgram()
{
	glDeleteProgram(mProgramId);
	mLinked = false;

	mUniformLocations.clear();
	mAttribLocations.clear();
}
