#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
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
	frustum.SetHorizontalFovAndAspectRatio(pi/180 * 90.0f, (float)(App->window->GetWidth() / App->window->GetHeight()));
 	frustum.SetPos(float3(0.f, 1.5f, 2.5f));
	frustum.SetFront(float3(0.0f, 0.0f, -1.f));
	frustum.SetUp(float3::unitY);

	return true;
}

update_status ModuleCamera::PreUpdate() {

	const float speed = 0.001f;


	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {

		frustum.SetPos(float3(frustum.Pos().x + speed, frustum.Pos().y, frustum.Pos().z));
	}
	else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		frustum.SetPos(float3(frustum.Pos().x - speed, frustum.Pos().y, frustum.Pos().z));
	}
	else if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
		frustum.SetPos(float3(frustum.Pos().x, frustum.Pos().y, frustum.Pos().z - speed));
	}
	else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		frustum.SetPos(float3(frustum.Pos().x, frustum.Pos().y, frustum.Pos().z + speed));
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

