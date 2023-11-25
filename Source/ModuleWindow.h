#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	virtual ~ModuleWindow();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	SDL_Window* GetWindow() const;
	SDL_Surface* GetWindowSurface() const;
	int GetWidth() const;
	int GetHeight() const;

	void SetSize(int width, int height);
	void Show();
	void Hide();

private:

	SDL_Window* window = NULL;
	SDL_Surface* screen_surface = NULL;

};

#endif // __ModuleWindow_H__