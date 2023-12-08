#include "ModuleRenderAssignment.h"

ModuleRenderAssignment::ModuleRenderAssignment()
{
}

ModuleRenderAssignment::~ModuleRenderAssignment()
{
}

bool ModuleRenderAssignment::Init()
{
	model = new Model();
	model->Load("../Game/Models/BakerHouse/BakerHouse.gltf");
	return true;
}

update_status ModuleRenderAssignment::PreUpdate()
{
	//TODO: Add drop action to Load new model.
	model->Draw();
	return update_status::UPDATE_CONTINUE;
}

bool ModuleRenderAssignment::CleanUp()
{

	return true;
}