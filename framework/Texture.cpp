#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& filename)
	: mFileName(filename)
	, mNumChannels(0)
	, mSamplerTextureIndex(0)
	, mLoaded(false)
{

}

Texture::~Texture()
{
	if (mGLTextureId != 0)
	{
		glDeleteTextures(1, &mGLTextureId);
	}
}

bool Texture::load()
{
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* imageData = stbi_load(mFileName.c_str(), &mImageSize.x, &mImageSize.y, &mNumChannels, 0);
	if (!imageData)
		return false;

	if (mNumChannels == 3)
	{
		mImageFormat = GL_RGB;
	}
	else if (mNumChannels == 4)
	{
		mImageFormat = GL_RGBA;
	}

	glGenTextures(1, &mGLTextureId);
	glBindTexture(GL_TEXTURE_2D, mGLTextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, mImageFormat, mImageSize.x, mImageSize.y, 0, mImageFormat, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
	mLoaded = true;

	return true;
}

void Texture::activateTexture(unsigned int samplerTextureIndex)
{
	if (!mLoaded)
		return;

	glActiveTexture(GL_TEXTURE0 + samplerTextureIndex);
	glBindTexture(GL_TEXTURE_2D, mGLTextureId);
	mSamplerTextureIndex = samplerTextureIndex;
}
