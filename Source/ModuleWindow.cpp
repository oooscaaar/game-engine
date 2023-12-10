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
		SDL_DisplayMode displayMode;

		if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
		{
			SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
		}

		int initialWidth = SCREEN_WIDTH;
		int initialHeight = SCREEN_HEIGHT;



		// Init in windowed mode with the default window size as half the desktop resolution
		if (displayMode.w > 0 && displayMode.h > 0) {
			initialWidth = displayMode.w / 2;
			initialHeight = displayMode.h / 2;
		}

		LOG("Initial window width: %d\n", initialWidth);
		LOG("Initial window height: %d\n", initialHeight);

		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;


		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, initialWidth, initialHeight, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			screen_surface = SDL_GetWindowSurface(window);
			LOG("CREATED WINDOW!");
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
	int width;
	SDL_GetWindowSize(window, &width, nullptr);
	return width;
}

int ModuleWindow::GetHeight() const
{
	int height;
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
