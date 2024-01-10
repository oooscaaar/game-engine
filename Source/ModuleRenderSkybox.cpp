#include "ModuleRenderSkybox.h"
#include "glew.h"
#include <string>
#include <filesystem>

ModuleRenderSkybox::ModuleRenderSkybox()
{
    texture = 0;
}

ModuleRenderSkybox::~ModuleRenderSkybox()
{
}

bool ModuleRenderSkybox::Init()
{
	LOG("Intitialize Module Render Skybox\n");

    LoadCubeMap();

	return true;
}

update_status ModuleRenderSkybox::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

bool ModuleRenderSkybox::CleanUp()
{
	return true;
}

unsigned ModuleRenderSkybox::LoadCubeMap()
{
    DirectX::ScratchImage image;

    HRESULT res = DirectX::LoadFromDDSFile(L"../Game/Textures/cubemap.dds", DirectX::DDS_FLAGS_NONE, nullptr, image);

    if (res == S_OK)
    {
        const DirectX::TexMetadata& metadata = image.GetMetadata();

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

        for (uint32_t i = 0; i < metadata.arraySize; ++i)
        {
            const DirectX::Image* face = image.GetImage(0, i, 0);

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, face->width, face->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, face->pixels);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return texture;
    }

    //TODO: Manage error

}
