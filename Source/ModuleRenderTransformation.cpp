#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleRenderTransformation.h"
#include "ModuleCamera.h"
#include "glew.h"
#include "MathGeoLib.h"


ModuleRenderTransformation::ModuleRenderTransformation()
{}

ModuleRenderTransformation::~ModuleRenderTransformation()
{}

bool ModuleRenderTransformation::Init()
{


	

	//CreateTriangleVBO
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // size = 3 float per vertex | stride = 0 is equivalent to stride = sizeof(float)*3

	// Create program
	unsigned vtx_shader = App->program->CompileShader(GL_VERTEX_SHADER, App->program->ReadShader("../Source/shaders/transformation.vert"));
	unsigned frg_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->ReadShader("../Source/shaders/hello_world.frag"));
	program = App->program->CreateProgram(vtx_shader, frg_shader);

	return true;
}

update_status ModuleRenderTransformation::PreUpdate()
{
	proj = App->camera->GetProjectionMatrix();
	model = float4x4::FromTRS(float3(0.0f, 0.0f, -0.5f), float3x3::RotateZ(0), float3(1.0f, 1.0f, 1.0f)); // 1. Translation, 2. Rotation, 3. Scale
	//view = float4x4::LookAt(float3(0.f, 0.0f, -1.0f), float3(0.0f, 0.0f, -0.5f), float3::unitY, float3::unitY);
	view = App->camera->GetViewMatrix();

	glUseProgram(program);

	glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &proj[0][0]);

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
