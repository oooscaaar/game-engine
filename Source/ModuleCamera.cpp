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
	InitFrustum();
	return true;
}

update_status ModuleCamera::PreUpdate() {
	
	speed = 3.f;
	const float rotationSpeed = 100.f;
	const float deltaTime = App->timer->GetDeltaTime();
	const float2& mouseMotion = App->input->GetMouseMotion();

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_REPEAT)
	{
		speed *= 2;
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_REPEAT) {
		Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), -mouseMotion.y * rotationSpeed * pi / 180 * deltaTime));
		Rotate(float3x3::RotateY(-mouseMotion.x * rotationSpeed * pi / 180 * deltaTime));
	}

	if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT)
	{
		frustum.SetPos(frustum.Pos() + (frustum.Front().Normalized() * speed * deltaTime));
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT)
	{
		frustum.SetPos(frustum.Pos() + (frustum.Front().Normalized() * -speed * deltaTime));
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT)
	{
		frustum.SetPos(frustum.Pos() + (frustum.WorldRight().Normalized() * -speed * deltaTime));
	}
	if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT)
	{
		frustum.SetPos(frustum.Pos() + (frustum.WorldRight().Normalized() * speed * deltaTime));
	}
	if (App->input->GetKey(SDL_SCANCODE_E) == KeyState::KEY_REPEAT)
	{
		frustum.SetPos(frustum.Pos() + (frustum.Up().Normalized() * -speed * deltaTime));
	}
	if (App->input->GetKey(SDL_SCANCODE_Q) == KeyState::KEY_REPEAT)
	{
		frustum.SetPos(frustum.Pos() + (frustum.Up().Normalized() * speed * deltaTime));
	}
	
	if (App->input->GetKey(SDL_SCANCODE_R) == KeyState::KEY_REPEAT) {
		InitFrustum();
	}

	if (App->input->GetKey(SDL_SCANCODE_LALT) == KeyState::KEY_REPEAT && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT) {
		const float3 focus = frustum.Pos() + frustum.Front(); 
		Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), -mouseMotion.y * rotationSpeed * pi/180 * deltaTime));
		Rotate(float3x3::RotateY(-mouseMotion.x * rotationSpeed * pi/180 * deltaTime));
		const float3 newFocus = frustum.Pos() + frustum.Front();
		frustum.SetPos((focus - newFocus) + frustum.Pos());
	}

	return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
	LOG("Destroying camera");
	return true;
}

void const ModuleCamera::Rotate(float3x3 rotationMatrix) {
	frustum.SetFront(rotationMatrix * frustum.Front().Normalized());
	frustum.SetUp(rotationMatrix * frustum.Up().Normalized());
}

float4x4 ModuleCamera::GetProjectionMatrix()
{
	return frustum.ProjectionMatrix();
}

float4x4 ModuleCamera::GetViewMatrix()
{
	return frustum.ViewMatrix();
}

const void ModuleCamera::InitFrustum() {
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio(pi / 180 * 90.0f, ((App->window->GetWidth())*1.f/App->window->GetHeight()));
	frustum.SetPos(float3(0.f, 0.5f, 1.5f));
	frustum.SetFront(-float3::unitZ);
	frustum.SetUp(float3::unitY);
}

void ModuleCamera::SetAspectRatio(int& width, int& height)
{
	if (height > 0 && width > 0) {
		frustum.SetHorizontalFovAndAspectRatio(frustum.HorizontalFov(), width * 1.f / height);
	}
	else {
		LOG("Error: Width or height are 0 or less");
	}

}

void ModuleCamera::Zoom(int& direction) {
	if (direction == 1) {
		frustum.SetPos(frustum.Pos() + (frustum.Front().Normalized() * speed * App->timer->GetDeltaTime()));
	}
	else if (direction == -1) {
		frustum.SetPos(frustum.Pos() + (frustum.Front().Normalized() * -speed * App->timer->GetDeltaTime()));
	}
}

