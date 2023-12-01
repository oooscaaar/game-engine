#pragma once
#include "Globals.h"
#include "Module.h"
#include "MathGeoLib/Math/float4x4.h"

class ModuleRenderQuad :
    public Module
{

    public:
		ModuleRenderQuad();
		~ModuleRenderQuad();

		bool Init();
		update_status PreUpdate();
		update_status Update();
		bool CleanUp();

	private:
		unsigned vbo;
		unsigned program;

		float4x4 proj = float4x4::identity;;
		float4x4 model = float4x4::identity;
		float4x4 view = float4x4::identity;
};

