#pragma once
#include "Module.h"
#include "Globals.h"

#ifndef DISABLE_IMGUI

typedef unsigned __int8 Uint8;

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:
	bool a = true;

};

#endif
