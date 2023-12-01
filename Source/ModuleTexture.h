#pragma once
#include "Module.h"


class ModuleTexture :
    public Module
{
    public:
	ModuleTexture();
	~ModuleTexture();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	private:
	unsigned int textureId = 0;
};

