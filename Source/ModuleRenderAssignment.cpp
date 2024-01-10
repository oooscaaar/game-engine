#include "ModuleRenderAssignment.h"
#include "ModuleLoader.h"

ModuleRenderAssignment::ModuleRenderAssignment()
{
}

ModuleRenderAssignment::~ModuleRenderAssignment()
{
}

bool ModuleRenderAssignment::Init()
{
	return true;
}

update_status ModuleRenderAssignment::PreUpdate()
{
	//if (!App->moduleLoader->GetModel()->GetMeshes().empty()) {
	//	App->moduleLoader->GetModel()->Draw();
	//}

	return update_status::UPDATE_CONTINUE;
}

bool ModuleRenderAssignment::CleanUp()
{
	delete model;
	return true;
}