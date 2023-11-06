#pragma once
#include "Module.h"
#include "Globals.h"
class ModuleRenderTransformation :
    public Module
{
    public:
	ModuleRenderTransformation();
	~ModuleRenderTransformation();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();
};

