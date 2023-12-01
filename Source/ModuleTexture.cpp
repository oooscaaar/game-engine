#include "ModuleTexture.h"
#include "DirectXTex/DirectXTex.h"
#include "glew.h"


ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Init()
{
	bool ret = true;

	DirectX::TexMetadata imageMetadata;
	DirectX::ScratchImage* image = new DirectX::ScratchImage();
	HRESULT hr = LoadFromDDSFile(L"../Game/Textures/Test-image-Baboon.dds",
	DirectX::DDS_FLAGS_NONE, &imageMetadata, *image);

	if (FAILED(hr)) {
		LOG("Error loading texture.\n");
		ret = false;
	}

	GLint internalFormat, format, type = 0;

	switch (imageMetadata.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported texture format.");
	}
	
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, imageMetadata.mipLevels - 1);

	if (imageMetadata.mipLevels == 0) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	for (size_t i = 0; i < imageMetadata.mipLevels; ++i)
	{
		const DirectX::Image* mip = image->GetImage(i, 0, 0);
		glTexImage2D(GL_TEXTURE_2D, i, internalFormat, mip->width, mip->height, 0, format, type, mip->pixels);
	}

	if (imageMetadata.mipLevels == 0) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	return ret;

}

update_status ModuleTexture::PreUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	return true;
}
