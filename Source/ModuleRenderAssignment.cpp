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
	model->Draw("../Game/Models/Duck/Duck.gltf");
	return update_status::UPDATE_CONTINUE;
}

bool ModuleRenderAssignment::CleanUp()
{

	return true;
}
