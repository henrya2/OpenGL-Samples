#pragma once

#include <string>
#include <gl/glew.h>
#include <glm/glm.hpp>

class Texture
{
public:
	Texture();

	Texture(const std::string& filename);

	~Texture();

	bool load();

	bool isLoaded() { return mLoaded; }

	int getWidth() const { return mImageSize.x; }

	int getHeight() const { return mImageSize.y; }

	const glm::ivec2& getImageSize() const { return mImageSize; }

	int getNumChannels() const { return mNumChannels; }

	unsigned int getSamplerTextureIndex() const { return mSamplerTextureIndex; }

	void activateTexture(unsigned int samplerTextureIndex);

protected:
	std::string mFileName;

	bool mLoaded;

	glm::ivec2 mImageSize;

	int mNumChannels;

	int mImageFormat;

	unsigned int mGLTextureId;

	unsigned int mSamplerTextureIndex;
};
