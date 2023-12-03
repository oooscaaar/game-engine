#pragma once
#include "Module.h"

class ModuleLoader :
    public Module
{
   public:
	ModuleLoader();
	~ModuleLoader();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

