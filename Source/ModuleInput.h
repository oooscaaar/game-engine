#pragma once
#include "Module.h"
#include "Globals.h"
#include "Math/float2.h"

typedef unsigned __int8 Uint8;

#define NUM_MOUSE_BUTTONS 5
#define MAX_KEYS 300


enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};


class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	const float2& GetMouseMotion() const;
	const float2& GetMousePosition() const;
	const signed short& GetMouseWheel();

private:
	KeyState*	keyboard = new KeyState[MAX_KEYS];;
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	float2		mouse_motion = { 0, 0 };
	float2		mouse = { 0, 0 };
	signed short mouseWheel = 0;
};