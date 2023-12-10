#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleLoader.h"
#include "SDL.h"
#include "imgui_impl_sdl2.h"
#include "ModuleCamera.h"


ModuleInput::ModuleInput()
{
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

ModuleInput::~ModuleInput()
{}

bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleInput::PreUpdate() {


	static SDL_Event sdlEvent;

	mouse_motion = { 0, 0 };

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if (mouse_buttons[i] == KEY_DOWN)
			mouse_buttons[i] = KEY_REPEAT;

		if (mouse_buttons[i] == KEY_UP)
			mouse_buttons[i] = KEY_IDLE;
	}


	while (SDL_PollEvent(&sdlEvent) != 0)
	{
		ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			return UPDATE_STOP;
			break;

		case SDL_WINDOWEVENT:
			switch (sdlEvent.window.event)
			{
				//TODO: Implement hide and show window

				//Hide window cases:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				//App->window->Hide();
				break;

				//Show window cases:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				//App->window->Show();
				break;
				
				//Resize window:
			case SDL_WINDOWEVENT_RESIZED:
				App->window->SetSize(sdlEvent.window.data1, sdlEvent.window.data2);
				App->camera->SetAspectRatio(sdlEvent.window.data1, sdlEvent.window.data2);
				break;
			}
			break;

		case SDL_MOUSEWHEEL:
			App->camera->Zoom(sdlEvent.wheel.y);
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouse_buttons[sdlEvent.button.button - 1] = KEY_DOWN;
			break;

		case SDL_MOUSEBUTTONUP:
			mouse_buttons[sdlEvent.button.button - 1] = KEY_UP;
			break;

		case SDL_MOUSEMOTION:
			mouse_motion.x = sdlEvent.motion.xrel;
			mouse_motion.y = sdlEvent.motion.yrel;
			mouse.x = sdlEvent.motion.x;
			mouse.y = sdlEvent.motion.y;
			break;

		case (SDL_DROPFILE):
			char* fileDirectory = sdlEvent.drop.file;
			SDL_ShowSimpleMessageBox(
				SDL_MESSAGEBOX_INFORMATION,
				"File Dropped",
				fileDirectory,
				App->window->GetWindow()
			);

			App->moduleLoader->LoadModel(fileDirectory);

			SDL_free(fileDirectory);
			break;
		}



	}

    return UPDATE_CONTINUE;
}


bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	delete keyboard;
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

const float2& ModuleInput::GetMousePosition() const
{
	return mouse;
}

const float2& ModuleInput::GetMouseMotion() const
{
	return mouse_motion;
}