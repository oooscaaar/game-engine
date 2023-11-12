#include "ModuleRenderTransformation.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "glew.h"
#include "Globals.h"
#include <Math/float3.h>
#include <Math/float4x4.h>
#include <Geometry/Frustum.h>
#include "ModuleOpenGL.h"



ModuleRenderTransformation::ModuleRenderTransformation()
{}

ModuleRenderTransformation::~ModuleRenderTransformation()
{}

bool ModuleRenderTransformation::Init()
{

	// Create program
	unsigned vtx_shader = App->GetProgram()->CompileShader(GL_VERTEX_SHADER, App->GetProgram()->ReadShader("../Source/shaders/transformation.vert"));
	unsigned frg_shader = App->GetProgram()->CompileShader(GL_FRAGMENT_SHADER, App->GetProgram()->ReadShader("../Source/shaders/hello_world.frag"));
	program = App->GetProgram()->CreateProgram(vtx_shader, frg_shader);
	glUseProgram(program);

	//CreateTriangleVBO
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	// Set Frustum
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * (float)(App->GetOpenGL()->GetWindowWidth() / App->GetOpenGL()->GetWindowHeight()));

	// Define the model, view and projection matrix
	proj = frustum.ProjectionMatrix();
	model = float4x4::FromTRS(float3(0.0f, 0.0f, -5.0f), float3x3::RotateZ(0), float3(1.0f, 1.0f, 1.0f)); // 1. Translation, 2. Rotation, 3. Scale
	view = float4x4::LookAt(float3(0.f, 0.0f, -1.0f), float3(0.0f, 0.0f, -0.5f), float3::unitY, float3::unitY);

	// Bind the VBO
	glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &proj[0][0]);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // size = 3 float per vertex | stride = 0 is equivalent to stride = sizeof(float)*3

	return true;
}

update_status ModuleRenderTransformation::PreUpdate()
{
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f)) * (App->GetOpenGL()->GetWindowWidth() / App->GetOpenGL()->GetWindowHeight());
	proj = frustum.ProjectionMatrix();

	// Draw triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);



	return UPDATE_CONTINUE;
}

update_status ModuleRenderTransformation::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleRenderTransformation::CleanUp()
{
	// Delete VBO
	glDeleteBuffers(1, &vbo);
	return true;
}
