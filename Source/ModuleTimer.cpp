#include "ModuleTimer.h"
#include "SDL.h"


ModuleTimer::ModuleTimer() {
}

ModuleTimer::~ModuleTimer() {
}

bool ModuleTimer::Init() {
	return true;
}

update_status ModuleTimer::PreUpdate() {
	float currentFrame = SDL_GetTicks();
	deltaTime = (currentFrame - lastFrame)/1000;
	lastFrame = currentFrame;
	return update_status::UPDATE_CONTINUE;
}

bool ModuleTimer::CleanUp() {
	return true;
}

const float ModuleTimer::GetDeltaTime() const {
	return deltaTime;
}
