#include "ModuleTexture.h"
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
	
	LOG("Intitialize Module Texture\n");
		
	
	DirectX::ScratchImage* image = new DirectX::ScratchImage();
	HRESULT hr = LoadFromDDSFile(L"../Game/Textures/Test-image-Baboon.dds",
	DirectX::DDS_FLAGS_NONE, &imageMetadata, *image);
	if (FAILED(hr)) {
		LOG("Error loading texture file.\n");
		ret = false;
	}

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

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, filterType, filterSubtype);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, imageMetadata.mipLevels - 1);


	for (size_t i = 0; i < imageMetadata.mipLevels; ++i)
	{
		const DirectX::Image* mip = image->GetImage(i, 0, 0);
		glTexImage2D(GL_TEXTURE_2D, i, internalFormat, mip->width, mip->height, 0, format, type, mip->pixels);
	}

	return ret;

}

update_status ModuleTexture::PreUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleTexture::CleanUp()
{
	glDeleteTextures(1, &texture);
	return true;
}

unsigned int const ModuleTexture::GetTexture() const
{
	return texture;
}

int const ModuleTexture::GetWidth() const
{
	return imageMetadata.width;
}

int const ModuleTexture::GetHeight() const
{
	return imageMetadata.height;
}

int const ModuleTexture::GetMipLevels() const
{
	return imageMetadata.mipLevels;
}

const char* ModuleTexture::GetFormat() const {
	switch (imageMetadata.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		return "GL_RGBA";
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		return "GL_BGRA";
	case DXGI_FORMAT_B5G6R5_UNORM:
		return "GL_BGR";
	default:
		return "Unknown texture format.";
	}
}

void ModuleTexture::SetFilter(TextureFilterType filterType, TextureFilterSubtype filterSubtype)
{
	this->filterType = filterType;
	this->filterSubtype = filterSubtype;
}

const char* ModuleTexture::GetFilterSubtype() const
{
	switch (filterSubtype)
	{
	case TextureFilterSubtype::NEAREST:
		return "GL_NEAREST";
	case TextureFilterSubtype::LINEAR:
		return "GL_LINEAR";
	case TextureFilterSubtype::NEAREST_MIPMAP_NEAREST:
		return "GL_NEAREST_MIPMAP_NEAREST";
	case TextureFilterSubtype::LINEAR_MIPMAP_NEAREST:
		return "GL_LINEAR_MIPMAP_NEAREST";
	case TextureFilterSubtype::NEAREST_MIPMAP_LINEAR:
		return "GL_NEAREST_MIPMAP_LINEAR";
	case TextureFilterSubtype::LINEAR_MIPMAP_LINEAR:
		return "GL_LINEAR_MIPMAP_LINEAR";
	default:
		return "Unknown texture filter subtype.";
	}
}

const char* ModuleTexture::GetFilterType() const
{
	switch (filterType)
	{
	case TextureFilterType::MIN_FILTER:
		return "GL_TEXTURE_MIN_FILTER";
	case TextureFilterType::MAX_FILTER:
		return "GL_TEXTURE_MAX_FILTER";
	default:
		return "Unknown texture filter type.";
	}
}