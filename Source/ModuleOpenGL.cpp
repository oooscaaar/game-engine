#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "glew.h"

ModuleOpenGL::ModuleOpenGL()
{
	// Initiliaze OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits

}

// Destructor
ModuleOpenGL::~ModuleOpenGL()
{

}

// Called before render is available
bool ModuleOpenGL::Init()
{
	LOG("Creating Renderer context");

	this->context = SDL_GL_CreateContext(App->GetWindow()->window);

	GLenum err = glewInit();

	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise

	glDisable(GL_SCISSOR_TEST); // Disable scissor test
	glDisable(GL_STENCIL_TEST); // Disable stencil test

	// TODO: Extract this logic
	//CreateTriangleVBO
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	// Create program
	unsigned vtx_shader = App->GetProgram()->CompileShader(GL_VERTEX_SHADER, App->GetProgram()->ReadShader("../Source/shaders/hello_world.vert"));
	unsigned frg_shader = App->GetProgram()->CompileShader(GL_FRAGMENT_SHADER, App->GetProgram()->ReadShader("../Source/shaders/hello_world.frag"));
	program = App->GetProgram()->CreateProgram(vtx_shader, frg_shader);

	return true;
}

update_status ModuleOpenGL::PreUpdate()
{
	int windowCurrentW;
	int windowCurrentH;
	SDL_GetWindowSize(App->GetWindow()->window, &windowCurrentW, &windowCurrentH);
	glViewport(0, 0, windowCurrentW, windowCurrentH);
	glClearColor(0.1f, 1.f, 0.1f, 1.0f); // Paint in RED :D
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TODO: Extract this logic

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleOpenGL::Update()
{
	// Render VBO Logic
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // size = 3 float per vertex | stride = 0 is equivalent to stride = sizeof(float)*3 
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	return UPDATE_CONTINUE;
}

update_status ModuleOpenGL::PostUpdate()
{
	SDL_GL_SwapWindow(App->GetWindow()->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleOpenGL::CleanUp()
{
	LOG("Destroying renderer\n");

	// Delete VBO
	glDeleteBuffers(1, &vbo);

	//Destroy window
	SDL_GL_DeleteContext(this->context);

	return true;
}

void ModuleOpenGL::WindowResized(unsigned width, unsigned height)
{
}

