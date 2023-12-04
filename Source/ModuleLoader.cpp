#include "ModuleLoader.h"
#include "Application.h"
#include "Mesh.h"

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

	Mesh* mesh = new Mesh;
	mesh->Load("../Game/Models/BakerHouse/BakerHouse.gltf");

	return true;
}

update_status ModuleLoader::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleLoader::Update()
{
	//Load Model

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

