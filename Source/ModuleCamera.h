#pragma once
#include "Module.h"


class ModuleCamera :
    public Module
{
    public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	bool CleanUp();
};

