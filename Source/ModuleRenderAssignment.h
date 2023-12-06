#pragma once
#include "Module.h"
#include "Model.h"

class ModuleRenderAssignment :
    public Module
{

    public:
	ModuleRenderAssignment();
	~ModuleRenderAssignment();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	private:
		Model* model = nullptr;
};

