#include "Globals.h"
#include "Application.h"
#include "ModuleCamera.h"
#include <Geometry/Frustum.h>


ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	bool ret = true;

	//frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
	//frustum.SetViewPlaneDistances(0.1f, 200.0f);
	//frustum.SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, 1.3f);

	//frustum.SetPos(float3(0.0f, 1.0f, -2.0f));
	//frustum.SetFront(float3::unitZ);
	//frustum.SetUp(float3::unitY);

	//float4x4 projectionGL = frustum.ProjectionMatrix().Transposed(); //<-- Important to transpose!

	////Send the frustum projection matrix to OpenGL
	//// direct mode would be:
	//glMatrixMode(GL_PROJECTION);
	//glLoadMatrixf(*projectionGL.v);

	return ret;
}

bool ModuleCamera::CleanUp()
{
	return true;
}

