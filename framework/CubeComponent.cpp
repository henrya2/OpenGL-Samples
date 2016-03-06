#include "CubeComponent.h"
#include "VertexStructs.h"

CubeComponent::CubeComponent()
{
	vertexBufferId = 0;
	indexBufferId = 0;

	mWidth = 100;
	mHeight = 100;
	mDepth = 100;
}

CubeComponent::~CubeComponent()
{
	freeResources();

}

void CubeComponent::onRender(const Camera& camera, const glm::mat4& worldMatrix)
{

}

void CubeComponent::updateRenderResources()
{
	freeResources();

	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);

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
}

void CubeComponent::freeResources()
{
	if (vertexBufferId)
	{
		glDeleteBuffers(1, &vertexBufferId);
	}
	if (indexBufferId)
	{
		glDeleteBuffers(1, &indexBufferId);
	}
}
