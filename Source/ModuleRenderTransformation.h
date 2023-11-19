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

	float4x4 proj = float4x4::identity;;
	//float4x4 model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f), float3x3::RotateZ(0), float3(1.0f, 1.0f, 1.0f)); // 1. Translation, 2. Rotation, 3. Scale
	float4x4 model = float4x4::identity;
	float4x4 view = float4x4::identity;
};
