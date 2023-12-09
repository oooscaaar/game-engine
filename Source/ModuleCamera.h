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
		update_status PreUpdate();
		bool CleanUp();
		const void InitFrustum();

		void const Rotate(float3x3 rotationMatrix);
		float4x4 GetProjectionMatrix();
		float4x4 GetViewMatrix();


	private:
		Frustum frustum;
		float4x4 proj;
		float4x4 model;
		float4x4 view;
};

