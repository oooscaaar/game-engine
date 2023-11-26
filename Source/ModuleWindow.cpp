#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

ModuleWindow::~ModuleWindow()
{
}

bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		int defaultWidth = SCREEN_WIDTH;
		int defaultHeight = SCREEN_HEIGHT;

		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;


		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, defaultWidth, defaultHeight, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

update_status ModuleWindow::PreUpdate()
{
 	return UPDATE_CONTINUE;
}

bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	return true;
}

SDL_Window* ModuleWindow::GetWindow() const
{
	return window;
}

int ModuleWindow::GetWidth() const
{
	int width = 640;
	SDL_GetWindowSize(window, &width, nullptr);
	return width;
}

int ModuleWindow::GetHeight() const
{
	int height = 480;
	SDL_GetWindowSize(window, nullptr, &height);
	return height;
}

void ModuleWindow::SetSize(int width, int height)
{
	SDL_SetWindowSize(window, width, height);
}

void ModuleWindow::Show()
{
	SDL_ShowWindow(window);
}

void ModuleWindow::Hide()
{
	SDL_HideWindow(window);
}
