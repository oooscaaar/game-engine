#pragma once
#include "Application.h"
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
	unsigned int texture = 0;
	unsigned int skyboxVAO = 0;
	unsigned int skyboxVBO = 0;
	unsigned int program = 0;
};

