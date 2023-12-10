#include "ModuleLoader.h"

ModuleLoader::ModuleLoader()
{
}

ModuleLoader::~ModuleLoader()
{
}

bool ModuleLoader::Init()
{
	model = new Model();
	LoadModel("Models/BakerHouse/BakerHouse.gltf");
	return true;
}

update_status ModuleLoader::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

bool ModuleLoader::CleanUp()
{
	delete model;
	return true;
}

void ModuleLoader::LoadModel(const char* filePath)
{
	this->model->Clear();
	this->model->Load(filePath);
}
