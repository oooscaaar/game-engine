#include "ModuleLoader.h"
#include "Application.h"

#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE 
#define TINYGLTF_IMPLEMENTATION /* Only in one of the includes */
#include "tiny_gltf.h"


ModuleLoader::ModuleLoader()
{
}
ModuleLoader::~ModuleLoader()
{
}

bool ModuleLoader::Init()
{
	LOG("Init ModuleLoader\n");

	tinygltf::TinyGLTF gltfContext;
	tinygltf::Model model;
	std::string error, warning, filePath;
	filePath = "../Game/Models/BakerHouse/BakerHouse.gltf";
	bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, filePath);
	if (!loadOk)
	{
		LOG("Error loading Model. %s\n", filePath, error.c_str());
		return false;
	}

	LOG("Model LOADED correctly. %s\n", filePath);
	return true;
}

update_status ModuleLoader::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoader::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoader::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleLoader::CleanUp()
{
	return true;
}

