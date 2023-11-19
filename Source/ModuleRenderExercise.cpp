#include "ModuleRenderExercise.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "glew.h"

ModuleRenderExercise::ModuleRenderExercise()
{}

ModuleRenderExercise::~ModuleRenderExercise()
{}

bool ModuleRenderExercise::Init()
{
	//CreateTriangleVBO
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // size = 3 float per vertex | stride = 0 is equivalent to stride = sizeof(float)*3 

	// Create program
	unsigned vtx_shader = App->program->CompileShader(GL_VERTEX_SHADER, App->program->ReadShader("../Source/shaders/hello_world.vert"));
	unsigned frg_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->ReadShader("../Source/shaders/hello_world.frag"));
	program = App->program->CreateProgram(vtx_shader, frg_shader);
	glUseProgram(program);

	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
	// Delete VBO
	glDeleteBuffers(1, &vbo);
	return true;
}
