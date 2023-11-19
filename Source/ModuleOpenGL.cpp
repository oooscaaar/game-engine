#include "Globals.h"
#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "glew.h"

ModuleOpenGL::ModuleOpenGL()
{

}

// Destructor
ModuleOpenGL::~ModuleOpenGL()
{

}

// Called before render is available
bool ModuleOpenGL::Init()
{
	LOG("Creating Renderer context");

	// Initiliaze OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits


	
	// Set OpenGL Context
	this->context = SDL_GL_CreateContext(App->window->GetWindow());
	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise
	glDisable(GL_SCISSOR_TEST); // Disable scissor test
	glDisable(GL_STENCIL_TEST); // Disable stencil test

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		LOG("Glew Init error: %s\n", glewGetErrorString(err));
		return false;
	}

	LOG("Using Glew %s", glewGetString(GLEW_VERSION));
	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	return true;
}

update_status ModuleOpenGL::PreUpdate()
{
	//SDL_GetWindowSize(App->window->GetWindow(), &windowWidth, &windowHeight);
	glClearColor(0.5f, 0.f, 0.5f, 1.0f); // Paint in Purple :D
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	//if(SDL_WINDOWEVENT_SIZE_CHANGED)

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleOpenGL::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleOpenGL::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->GetWindow());

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleOpenGL::CleanUp()
{
	LOG("Destroying renderer\n");

	//Destroy window
	SDL_GL_DeleteContext(this->context);

	return true;
}

void ModuleOpenGL::WindowResized(unsigned width, unsigned height)
{
}

