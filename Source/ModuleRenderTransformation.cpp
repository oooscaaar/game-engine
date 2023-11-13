#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleProgram.h"
#include "ModuleRenderTransformation.h"
#include "glew.h"
#include <Math/MathConstants.h>
#include <Math/float3x3.h>


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
	Frustum frustum;
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 200.0f);
	frustum.SetHorizontalFovAndAspectRatio(75.f, (float)(App->GetOpenGL()->GetWindowWidth() / App->GetOpenGL()->GetWindowHeight()));
	frustum.SetPos(float3(0.0f, 1.0f, -2.0f));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);


	proj = float4x4::identity; //TODO: Investigate why -> either frustum.ProjectionMatrix() nor frustum.ProjectionMatrix().Transposed() are not generating the correct matrix.
	

	model = float4x4::identity;
	//model = float4x4::FromTRS(float3(0.0f, 0.0f, 5.0f), float3x3::RotateZ(0), float3(1.0f, 1.0f, 1.0f)); // 1. Translation, 2. Rotation, 3. Scale

	view = float4x4::LookAt(float3(0.f, 0.0f, -1.0f), float3(0.0f, 0.0f, -0.5f), float3::unitY, float3::unitY);
	//view = float4x4::identity;//frustum.ViewMatrix();


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
	//frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f)) * (App->GetOpenGL()->GetWindowWidth() / App->GetOpenGL()->GetWindowHeight());
	//proj = frustum.ProjectionMatrix();

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
