#include "Globals.h"
#include "Application.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "ModuleCamera.h"
#include "SDL.h"
#include "glew.h"
#include "debugdraw.h"

ModuleOpenGL::ModuleOpenGL()
{

}

// Destructor
ModuleOpenGL::~ModuleOpenGL()
{

}

void APIENTRY openglCallbackFunction(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam
) {
	(void)source; (void)type; (void)id;
	(void)severity; (void)length; (void)userParam;
	fprintf(stderr, "%s\n", message);
	if (severity == GL_DEBUG_SEVERITY_HIGH) {
		fprintf(stderr, "aborting...\n");
		abort();
	}
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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG); // Enable context debug flags
	
	// Set OpenGL Context
	this->context = SDL_GL_CreateContext(App->window->GetWindow());
	
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

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise
	glDisable(GL_SCISSOR_TEST); // Disable scissor test
	glDisable(GL_STENCIL_TEST); // Disable stencil test

	// Enable debugging
	glEnable(GL_DEBUG_OUTPUT); // Enable Output Callbacks
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Output Callbacks
	glDebugMessageCallback(openglCallbackFunction, 0); // Set Callback Function
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, true); //Filter notifications

	return true;
}

update_status ModuleOpenGL::PreUpdate()
{

	glClearColor(0.5f, 0.f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	dd::xzSquareGrid(-10, 10, 0.0f, 0.5f, dd::colors::Gray);
	dd::axisTriad(float4x4::identity, 0.05f, 0.5f);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleOpenGL::Update()
{
	//Temporary draw triangle from ModuleRenderExercise so we can verify DebugDraw
	

	int windowWidth, windowHeight;
	SDL_GetWindowSize(App->window->GetWindow(), &windowWidth, &windowHeight);

	App->debugDraw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMatrix(), windowWidth, windowHeight);

	//glDrawArrays(GL_TRIANGLES, 0, 3);
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

	SDL_GL_DeleteContext(context);

	return true;
}

//void ModuleOpenGL::WindowResized(unsigned width, unsigned height)
//{
//}

