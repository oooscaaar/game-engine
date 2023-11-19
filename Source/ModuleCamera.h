#pragma once
#include "Module.h"
#include <Math/float4x4.h>
#include "MathGeoLib.h"



class ModuleCamera :
    public Module
{
    public:
		ModuleCamera();
		~ModuleCamera();

		bool Init();
		bool CleanUp();

		float4x4 GetProjectionMatrix();
		float4x4 GetViewMatrix();

	private:
		Frustum frustum;
		float4x4 proj;
		float4x4 model;
		float4x4 view;
};

