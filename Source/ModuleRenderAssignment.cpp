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
	//model->Draw("../Game/Models/BakerHouse/BakerHouse.gltf");
	model->Draw();
	return update_status::UPDATE_CONTINUE;
}

bool ModuleRenderAssignment::CleanUp()
{

	return true;
}

//void ModuleRenderAssignment::Draw()
//{
//	model->Draw("../Game/Models/BakerHouse/BakerHouse.gltf");
//}
