#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleTimer;
class ModuleOpenGL;
class ModuleDebugDraw;
class ModuleWindow;
class ModuleInput;
class ModuleProgram;
class ModuleCamera;

class ModuleRenderSkybox;




class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
    
    ModuleTimer* timer = nullptr;
    ModuleOpenGL* render = nullptr;
    ModuleDebugDraw* debugDraw = nullptr;
    ModuleWindow* window = nullptr;
    ModuleProgram* program = nullptr;
    ModuleCamera* camera = nullptr;
	ModuleInput* input = nullptr;
    ModuleRenderSkybox* renderSkybox = nullptr;
    

private:

    std::list<Module*> modules;

};

extern Application* App;
