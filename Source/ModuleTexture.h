#pragma once
#include "Module.h"
#include "DirectXTex/DirectXTex.h"
#include "glew.h"
#include <string>
// write an enum type definition with tecture filtering options
enum TextureFilterType
{
	MIN_FILTER = GL_TEXTURE_MIN_FILTER,
	MAX_FILTER = GL_TEXTURE_MAG_FILTER,
};

enum TextureFilterSubtype
{
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR,
	NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
};

class ModuleTexture :
    public Module
{
    public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	unsigned int const GetTexture() const;
	int const GetWidth() const;
	int const GetHeight() const;
	int const GetMipLevels() const;
	const char* GetFormat() const;
	void SetFilter(TextureFilterType filterType, TextureFilterSubtype filterSubtype = TextureFilterSubtype::LINEAR);
	const char* GetFilterType() const;
	const char* GetFilterSubtype() const;
	unsigned int Load(const std::string& resourceName, const std::string& filePath);
	void Delete(unsigned int& texture);



	private:

	unsigned int texture;
	DirectX::ScratchImage* image = nullptr;
	DirectX::TexMetadata imageMetadata;
	GLint internalFormat, format, type = 0;
	TextureFilterType filterType = TextureFilterType::MIN_FILTER;
	TextureFilterSubtype filterSubtype = TextureFilterSubtype::LINEAR_MIPMAP_LINEAR;

	const std::string& GetDirFromFilePath(const std::string& filePath);

	};
