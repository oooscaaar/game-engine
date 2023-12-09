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
	App->moduleLoader->GetModel()->Draw();
	return update_status::UPDATE_CONTINUE;
}

bool ModuleRenderAssignment::CleanUp()
{

	return true;
}