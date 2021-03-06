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

	mWidth = 4;
	mHeight = 4;
	mDepth = 4;

	mTexture = nullptr;

	const std::string defaultVertexShaderStr =
		"#version 330\n"
		"in vec3 vertexPosition;\n"
		"in vec4 vertexColor;\n"

		"out vec4 fragmentColor;\n"

		"uniform mat4 MVPMatrix;\n"

		"uniform mat4 ModelViewMatrix;\n"

		"uniform mat3 NormalMatrix;\n"
		
		"void main()\n"
		"{\n"
		"	gl_Position = MVPMatrix * vec4(vertexPosition.xyz, 1);\n"
		
		"	fragmentColor = vertexColor;\n"
		"}\n";

	const std::string defaultFragmentShaderStr =
		"#version 330\n"
		"out vec4 outputColor;	//fragment shader output\n"

		"in vec4 fragmentColor;\n"

		"void main()\n"
		"{\n"
		"	//set the interpolated color as the shader output\n"
		"	outputColor = vec4(fragmentColor.rgb, 1.0);\n"
		"}\n";

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
	glm::mat4 modelView = camera.getViewMatrix() * worldMatrix;
	glm::mat3 normalMatrix = glm::inverse(glm::transpose(glm::mat3(modelView)));

	if (mGLSLProgram)
	{
		mGLSLProgram->use();
		mGLSLProgram->setUniform("MVPMatrix", mvp);
		mGLSLProgram->setUniform("ModelViewMatrix", modelView);
		mGLSLProgram->setUniform("NormalMatrix", normalMatrix);

		glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);

		GLint attribLoc = mGLSLProgram->getAttributeLocation("vertexPosition");
		GLsizei stride = sizeof(VertexPositionColorNormalUV);
		if (attribLoc != GL_INVALID_INDEX)
		{
			glEnableVertexAttribArray(attribLoc);
			void* offset = VERTEX_ATTRIB_OFFSET(VertexPositionColorNormalUV, position);
			GLint elementSize = sizeof(VertexPositionColorNormalUV::position) / sizeof(float);
			glVertexAttribPointer(attribLoc, elementSize, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		}
		attribLoc = mGLSLProgram->getAttributeLocation("vertexColor");
		if (attribLoc != GL_INVALID_INDEX)
		{
			glEnableVertexAttribArray(attribLoc);
			void* offset = VERTEX_ATTRIB_OFFSET(VertexPositionColorNormalUV, color);
			GLint elementSize = sizeof(VertexPositionColorNormalUV::color) / sizeof(float);
			glVertexAttribPointer(attribLoc, elementSize, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		}
		attribLoc = mGLSLProgram->getAttributeLocation("vertexNormal");
		if (attribLoc != GL_INVALID_INDEX)
		{
			glEnableVertexAttribArray(attribLoc);
			void* offset = VERTEX_ATTRIB_OFFSET(VertexPositionColorNormalUV, normal);
			GLint elementSize = sizeof(VertexPositionColorNormalUV::normal) / sizeof(float);
			glVertexAttribPointer(attribLoc, elementSize, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		}
		attribLoc = mGLSLProgram->getAttributeLocation("vertexUV");
		if (attribLoc != GL_INVALID_INDEX)
		{
			glEnableVertexAttribArray(attribLoc);
			void* offset = VERTEX_ATTRIB_OFFSET(VertexPositionColorNormalUV, uv);
			GLint elementSize = sizeof(VertexPositionColorNormalUV::uv) / sizeof(float);
			glVertexAttribPointer(attribLoc, elementSize, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		}


		if (mTexture && mTexture->isLoaded())
		{
			mTexture->activateTexture(0);
			mGLSLProgram->setUniform("textureSampler", 0);
		}

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
		for (int j = 0; j < 2; ++j)
		{
			indexBufferData[indexCount++] = i * 4 + 0;
			indexBufferData[indexCount++] = i * 4 + (j + 1);
			indexBufferData[indexCount++] = i * 4 + (j + 2);
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

void CubeComponent::onAttached()
{
	updateRenderResources();
}
