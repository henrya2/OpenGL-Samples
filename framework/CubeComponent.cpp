#include "CubeComponent.h"
#include "VertexStructs.h"
#include "Camera.h"
#include "GLSLProgram.h"
#include "Texture.h"

#include <vector>

CubeComponent::CubeComponent()
{
	mVertexBufferId = 0;
	mIndexBufferId = 0;

	mWidth = 100;
	mHeight = 100;
	mDepth = 100;

	mTexture = nullptr;

	const std::string defaultVertexShaderStr =
		"in vec3 vertexColor;"
		"in vec3 position;"
		
		"out vec3 fragmentColor;"
		
		"uniform mat4 MVP;"
		
		"void main()"
		"{"
		"	gl_Position = MVP * vec4(position.xyz, 1);"
		
		"	fragmentColor = vertexColor;"
		"}";

	const std::string defaultFragmentShaderStr =
		"layout(location = 0) out vec4 outputColor;	//fragment shader output"

		"in vec3 fragmentColor;"

		"void main()"
		"{"
		"//set the interpolated colour as the shader output"
		"outputColor = vec4(fragmentColor, 1.0f);"
		"}";

	GLSLProgram* defaultGLSLProgram = new GLSLProgram();

	defaultGLSLProgram->compileShader(GLSLShaderType::VERTEX, defaultVertexShaderStr);
	defaultGLSLProgram->compileShader(GLSLShaderType::FRAGMENT, defaultFragmentShaderStr);
	defaultGLSLProgram->link();

	setGLSLProgram(defaultGLSLProgram);
}

CubeComponent::~CubeComponent()
{
	freeResources();
}

void CubeComponent::setSize(float width, float height, float depth, bool needUpdateResources /*= true*/)
{
	mWidth = width;
	mHeight = height;
	mDepth = depth;

	if (needUpdateResources)
	{
		updateRenderResources();
	}
}

void CubeComponent::onRender(const Camera& camera, const glm::mat4& worldMatrix)
{
	glm::mat4 mvp = camera.getVP() * worldMatrix;

	if (mGLSLProgram)
	{
		mGLSLProgram->use();
		mGLSLProgram->setUniform("MVP", mvp);

		GLint attribLoc = mGLSLProgram->getAttributeLocation("vertexPosition");
		if (attribLoc != GL_INVALID_INDEX)
		{
			glEnableVertexAttribArray(attribLoc);
			glVertexAttribPointer(attribLoc, sizeof(VertexPositionColorNormalUV::position), GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_OFFSET(VertexPositionColorNormalUV, position), nullptr);
		}
		attribLoc = mGLSLProgram->getAttributeLocation("vertexColor");
		if (attribLoc != GL_INVALID_INDEX)
		{
			glEnableVertexAttribArray(attribLoc);
			glVertexAttribPointer(attribLoc, sizeof(VertexPositionColorNormalUV::color), GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_OFFSET(VertexPositionColorNormalUV, color), nullptr);
		}
		attribLoc = mGLSLProgram->getAttributeLocation("vertexNormal");
		if (attribLoc != GL_INVALID_INDEX)
		{
			glEnableVertexAttribArray(attribLoc);
			glVertexAttribPointer(attribLoc, sizeof(VertexPositionColorNormalUV::normal), GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_OFFSET(VertexPositionColorNormalUV, normal), nullptr);
		}
		attribLoc = mGLSLProgram->getAttributeLocation("vertexUV");
		if (attribLoc != GL_INVALID_INDEX)
		{
			glEnableVertexAttribArray(attribLoc);
			glVertexAttribPointer(attribLoc, sizeof(VertexPositionColorNormalUV::uv), GL_FLOAT, GL_FALSE, VERTEX_ATTRIB_OFFSET(VertexPositionColorNormalUV, uv), nullptr);
		}


		if (mTexture && mTexture->isLoaded())
		{
			mTexture->activateTexture(0);
			mGLSLProgram->setUniform("textureSampler", 0);
		}


		glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);

		glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, nullptr);
	}
}

void CubeComponent::updateRenderResources()
{
	freeResources();

	glGenBuffers(1, &mVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);

	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(VertexPositionColorNormalUV), nullptr, GL_STATIC_DRAW);

	void* data = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	VertexPositionColorNormalUV* vertexData = (VertexPositionColorNormalUV*)data;

	float halfWidth = mWidth / 2;
	float halfHeight = mHeight / 2;
	float halfDepth = mDepth / 2;

	int vertexIndex = 0;
	// +Z face
	vertexData[vertexIndex++] =
	{
		{-halfWidth, -halfHeight, halfDepth},
		{1.0f, 1.0f, 1.0f, 1.0f},
		{0, 0, 1.0f},
		{0, 0}
	};
	vertexData[vertexIndex++] =
	{
		{ halfWidth, -halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 0, 1.0f },
		{ 1.0f, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ halfWidth, halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 0, 1.0f },
		{ 1.0f, 1.0f }
	};
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 0, 1.0f },
		{ 0, 1.0f }
	};

	// -Z face
	vertexData[vertexIndex++] =
	{
		{ halfWidth, -halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 0, -1.0f },
		{ 0, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, -halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 0, -1.0f },
		{ 1.0f, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 0, -1.0f },
		{ 1.0f, 1.0f }
	};
	vertexData[vertexIndex++] =
	{
		{ halfWidth, halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 0, -1.0f },
		{ 0, 1.0f }
	};

	// +X face
	vertexData[vertexIndex++] =
	{
		{ halfWidth, -halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 0, 0 },
		{ 0, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ halfWidth, -halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 0, 0 },
		{ 1.0f, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ halfWidth, halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 0, 0 },
		{ 1.0f, 1.0f }
	};
	vertexData[vertexIndex++] =
	{
		{ halfWidth, halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 1.0f, 0, 0 },
		{ 0, 1.0f }
	};

	// -X face
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, -halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ -1.0f, 0, 0 },
		{ 0, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, -halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ -1.0f, 0, 0 },
		{ 1.0f, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ -1.0f, 0, 0 },
		{ 1.0f, 1.0f }
	};
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ -1.0f, 0, 0 },
		{ 0, 1.0f }
	};

	// +Y face
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 1.0f, 0 },
		{ 0, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ halfWidth, halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 1.0f, 0 },
		{ 1.0f, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ halfWidth, halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 1.0f, 0 },
		{ 1.0f, 1.0f }
	};
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, 1.0f, 0 },
		{ 0, 1.0f }
	};

	// -Y face
	vertexData[vertexIndex++] =
	{
		{ halfWidth, -halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, -1.0f, 0 },
		{ 0, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, -halfHeight, halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, -1.0f, 0 },
		{ 1.0f, 0 }
	};
	vertexData[vertexIndex++] =
	{
		{ -halfWidth, -halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, -1.0f, 0 },
		{ 1.0f, 1.0f }
	};
	vertexData[vertexIndex++] =
	{
		{ halfWidth, -halfHeight, -halfDepth },
		{ 1.0f, 1.0f, 1.0f, 1.0f },
		{ 0, -1.0f, 0 },
		{ 0, 1.0f }
	};

	glUnmapBuffer(GL_ARRAY_BUFFER);

	glGenBuffers(1, &mIndexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 6 * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);
	data = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	unsigned int* indexBufferData = (unsigned int*)data;

	int indexCount = 0;
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j + 2 < 4; ++j)
		{
			indexBufferData[indexCount++] = i * 6 + 0;
			indexBufferData[indexCount++] = i * 6 + (j + 1);
			indexBufferData[indexCount++] = i * 6 + (j + 2);
		}
	}

	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}

void CubeComponent::setTexture(Texture* texture)
{
	mTexture = texture;
}

void CubeComponent::freeResources()
{
	if (mVertexBufferId)
	{
		glDeleteBuffers(1, &mVertexBufferId);
	}
	if (mIndexBufferId)
	{
		glDeleteBuffers(1, &mIndexBufferId);
	}
}
