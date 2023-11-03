#pragma once
#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

class ModuleRenderExercise :
    public Module
{

public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

private:
	unsigned vbo;
	unsigned program;
};

