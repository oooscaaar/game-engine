#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "ModuleTimer.h"
#include "glew.h"
#include "SDL.h"
#include "debugdraw.h"
#include <Geometry/Frustum.h>


ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio(pi/180 * 90.0f, 4/3.f);
 	frustum.SetPos(float3(0.f, 1.f, 0.f));
	frustum.SetFront(-float3::unitZ);
	frustum.SetUp(float3::unitY);

	return true;
}

update_status ModuleCamera::PreUpdate() {

	const float speed = 2.f;
	const float deltaTime = App->timer->GetDeltaTime();

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {

		frustum.SetPos(float3(frustum.Pos().x + speed*deltaTime, frustum.Pos().y, frustum.Pos().z));
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		frustum.SetPos(float3(frustum.Pos().x - speed*deltaTime, frustum.Pos().y, frustum.Pos().z));
	}
	else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		frustum.SetPos(float3(frustum.Pos().x, frustum.Pos().y, frustum.Pos().z - speed*deltaTime));
	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		frustum.SetPos(float3(frustum.Pos().x, frustum.Pos().y, frustum.Pos().z + speed*deltaTime));
	}
	
	return UPDATE_CONTINUE;
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

