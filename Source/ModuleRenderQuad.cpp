﻿#include "ModuleRenderQuad.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "glew.h"
#include "MathGeoLib.h"
#include "SDL.h"
#include "ModuleTexture.h"


ModuleRenderQuad::ModuleRenderQuad()
{}
ModuleRenderQuad::~ModuleRenderQuad()
{}

bool ModuleRenderQuad::Init()
{

	float buffer_data[] =
	{
		-1.0f, -1.0f, 0.0f, // ← Vertex 0 position
		1.0f, 1.0f, 0.0f, // ← Vertex 1 position
		-1.0f, 1.0f, 0.0f, // ← Vertex 2 position
		-1.0f, -1.0f, 0.0f, // ← Vertex 3 position
		1.0f, -1.0f, 0.0f, // ← Vertex 4 position
		1.0f, 1.0f, 0.0f, // ← Vertex 5 position
		0.0f, 1.0f, // ← Vertex 0 Texture coordinates
		1.0f, 0.0f, // ← Vertex 1 Texture coordinates
		0.0f, 0.0f, // ← Vertex 2 Texture coordinates
		0.0f, 1.0f, // ← Vertex 3 Texture coordinates
		1.0f, 1.0f, // ← Vertex 4 Texture coordinates
		1.0f, 0.0f // ← Vertex 5 Texture coordinates
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);


	// Color Attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,(void*)(sizeof(float)*18));
	glEnableVertexAttribArray(1);

	// Create program
	unsigned vtx_shader = App->program->CompileShader(GL_VERTEX_SHADER, App->program->ReadShader("../Source/Shaders/texture.vert"));
	unsigned frg_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->ReadShader("../Source/Shaders/texture.frag"));
	program = App->program->CreateProgram(vtx_shader, frg_shader);

	return true;
}

update_status ModuleRenderQuad::PreUpdate()
{
	proj = App->camera->GetProjectionMatrix();
	model = float4x4::FromTRS(float3(0.0f, 0.0f, -0.5f), float3x3::RotateZ(0), float3(1.0f, 1.0f, 1.0f)); // 1. Translation, 2. Rotation, 3. Scale
	//view = float4x4::LookAt(float3(0.f, 0.0f, -1.0f), float3(0.0f, 0.0f, -0.5f), float3::unitY, float3::unitY);
	view = App->camera->GetViewMatrix();


	glUseProgram(program);
	
	// Update the uniform model, view & projection matrices
	GLint vertexModelLocation = glGetUniformLocation(program, "model");
	GLint vertexViewLocation = glGetUniformLocation(program, "view");
	GLint vertexProjLocation = glGetUniformLocation(program, "proj");

	glUniformMatrix4fv(vertexModelLocation, 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(vertexViewLocation, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(vertexProjLocation, 1, GL_TRUE, &proj[0][0]);
	
	// Bind texture
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, App->texture->GetTexture());

	// Draw triangle
	glDrawArrays(GL_TRIANGLES, 0, 6);

	return UPDATE_CONTINUE;
}

bool ModuleRenderQuad::CleanUp()
{

	// Delete VBO
	glDeleteBuffers(1, &vbo);
	return true;
}
