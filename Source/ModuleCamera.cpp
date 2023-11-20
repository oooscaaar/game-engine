#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "ModuleCamera.h"
#include <Geometry/Frustum.h>
#include "glew.h"
#include "debugdraw.h"


ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	frustum.SetKind(FrustumSpaceGL, FrustumLeftHanded);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio(pi/180 * 90.0f, (float)(App->window->GetWidth() / App->window->GetHeight()));
 	frustum.SetPos(float3(0.f, 1.5f, -2.5f));
	frustum.SetFront(float3(0.0f, 0.0f, 1.f));
	frustum.SetUp(float3::unitY);

	return true;
}

bool ModuleCamera::CleanUp()
{
	return true;
}

float4x4 ModuleCamera::GetProjectionMatrix()
{
	return frustum.ProjectionMatrix();
}

float4x4 ModuleCamera::GetViewMatrix()
{
	return frustum.ViewMatrix();
}

