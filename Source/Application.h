#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleDebugDraw;
class ModuleWindow;
class ModuleProgram;
class ModuleEditor;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleRenderTransformation;
class ModuleCamera;
class ModuleTexture;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    ModuleOpenGL* render = nullptr;
    ModuleDebugDraw* debugDraw = nullptr;
    ModuleWindow* window = nullptr;
    ModuleProgram* program = nullptr;
    ModuleInput* input = nullptr;
    ModuleRenderExercise* render_exercise = nullptr;
    ModuleRenderTransformation* render_transformation = nullptr;
    ModuleEditor* editor = nullptr;
    ModuleCamera* camera = nullptr;
    ModuleTexture* texture = nullptr;
    

private:

    std::list<Module*> modules;

};

extern Application* App;
