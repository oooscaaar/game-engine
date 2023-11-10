#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"

typedef unsigned __int8 Uint8;


class ModuleRenderTransformation :
	public Module
{
public:
	ModuleRenderTransformation();
	~ModuleRenderTransformation();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

private:
	unsigned vbo;
	unsigned program;
	float4x4 proj;
	float4x4 model;
	float4x4 view;
	Frustum frustum;
};
