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

		void SetFOV(unsigned int fov);
		void SetAspectRatio(float aspect_ratio);
		void SetPlaneDistances();
		void SetPosition(float3 position);
		void SetOrientation(float3x3 orientation);
		void LookAt(float3 target);
		float4x4 GetProjectionMatrix();
		float4x4 GetViewMatrix();

	private:
		Frustum* frustum;

};

