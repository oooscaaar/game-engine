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
	//float4x4 view = float4x4::LookAt(float3(0.f, 0.0f, -1.0f), float3(0.0f, 0.0f, -1.0f), float3(0.0f, 1.0f, 0.0f), float3(0.0f, 1.0f, 0.0f));
	float4x4 view;
};
