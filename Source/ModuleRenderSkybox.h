#pragma once
#include "Module.h"
#include "DirectXTex/DirectXTex.h"

class ModuleRenderSkybox :
    public Module
{
    public:
	ModuleRenderSkybox();
	~ModuleRenderSkybox();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	unsigned LoadCubeMap();
	unsigned texture;
};

