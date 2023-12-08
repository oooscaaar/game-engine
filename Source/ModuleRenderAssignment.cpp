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
	return true;
}

update_status ModuleRenderAssignment::PreUpdate()
{
	//model->Draw("../Game/Models/BakerHouse/BakerHouse.gltf");
	model->Draw("../Game/Models/BakerHouse/BakerHouse.gltf");
	return update_status::UPDATE_CONTINUE;
}

bool ModuleRenderAssignment::CleanUp()
{

	return true;
}
