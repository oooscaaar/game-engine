#include "ModuleTexture.h"
#include "DirectXTex/DirectXTex.h"


ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Init()
{

	bool ret = true;

	DirectX::TexMetadata info;
	DirectX::ScratchImage* image = new DirectX::ScratchImage();
	HRESULT hr = LoadFromDDSFile(L"../Game/Textures/Test-image-Baboon.dds",
		DirectX::DDS_FLAGS_NONE, &info, *image);

	if (FAILED(hr)) {
		LOG("Error loading texture.\n");
		ret = false;
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
