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
	bool ret = true;

	// Set Frustum
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio(75.f, (float)(App->window->GetWidth() / App->window->GetHeight()));

	frustum.SetPos(float3(0.0f, 1.0f, -2.0f));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);

	//float4x4 projectionGL = frustum.ProjectionMatrix().Transposed();
	//glMatrixMode(GL_PROJECTION);
	//glLoadMatrixf(*projectionGL.v);

	//TODO: REfactor -> Place where it belongs
	proj = float4x4::identity; //TODO: Investigate why -> either frustum.ProjectionMatrix() nor frustum.ProjectionMatrix().Transposed() are not generating the correct matrix.
	model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f), float3x3::RotateZ(0), float3(1.0f, 1.0f, 1.0f)); // 1. Translation, 2. Rotation, 3. Scale
	view = float4x4::LookAt(float3(0.3f, 0.3f, -1.0f), float3(0.0f, 0.0f, -0.5f), float3::unitY, float3::unitY);


	// Bind the VBO
	glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &proj[0][0]);



	return ret;
}

update_status ModuleCamera::PreUpdate()
{
	//dd::xzSquareGrid(-10, 10, 0.0f, 0.5f, dd::colors::Gray);
	//dd::axisTriad(float4x4::identity, 0.05f, 0.5f);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
	//App->GetDebugDraw()->Draw(view, proj, App->GetOpenGL()->GetWindowWidth(), App->GetOpenGL()->GetWindowHeight());
	return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
	return true;
}

