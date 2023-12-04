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
class ModuleCamera;
class ModuleTexture;
class ModuleRenderExercise;
class ModuleRenderTransformation;
class ModuleRenderQuad;
class ModuleLoader;
class Mesh;

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
    ModuleEditor* editor = nullptr;
    ModuleCamera* camera = nullptr;
    ModuleTexture* texture = nullptr;
    ModuleLoader* loader = nullptr;
    //Exercise modules
    ModuleRenderExercise* render_exercise = nullptr;
    ModuleRenderTransformation* render_transformation = nullptr;
    ModuleRenderQuad* render_quad = nullptr;
    

private:

    std::list<Module*> modules;

};

extern Application* App;
