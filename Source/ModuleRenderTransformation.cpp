#include "ModuleRenderTransformation.h"
#include "Application.h"

ModuleRenderTransformation::ModuleRenderTransformation()
{}

ModuleRenderTransformation::~ModuleRenderTransformation()
{}

bool ModuleRenderTransformation::Init() {
	return true;
}

update_status ModuleRenderTransformation::PreUpdate() {
	return UPDATE_CONTINUE;
}

bool ModuleRenderTransformation::CleanUp() {
	return true;
}
