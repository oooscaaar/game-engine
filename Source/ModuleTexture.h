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
	unsigned int const GetTexture() const;

	private:
	unsigned int texture;
};

