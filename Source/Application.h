#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleTimer;
class ModuleOpenGL;
class ModuleDebugDraw;
class ModuleWindow;
class ModuleProgram;
class ModuleEditor;
class ModuleTextures;
class ModuleInput;
class ModuleCamera;
class ModuleTexture;
class ModuleLoader;

class ModuleRenderAssignment;

class Model;



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
    ModuleInput* input = nullptr;
    ModuleEditor* editor = nullptr;
    ModuleCamera* camera = nullptr;
    ModuleTexture* texture = nullptr;
    ModuleLoader* moduleLoader = nullptr;

    ModuleRenderAssignment* renderAssignment = nullptr;
    

private:

    std::list<Module*> modules;

};

extern Application* App;
