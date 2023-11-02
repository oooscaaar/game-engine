#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleWindow;
class ModuleProgram;
class ModuleEditor;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    ModuleOpenGL* GetOpenGL() { return render; }
    ModuleWindow* GetWindow() { return window; }
    ModuleProgram* GetProgram() { return program; }
    ModuleInput*  GetInput() { return input; }
    ModuleEditor* GetEditor() { return editor; }

private:

    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleProgram* program = nullptr;
    ModuleEditor* editor = nullptr;
    ModuleInput* input = nullptr;

    std::list<Module*> modules;

};

extern Application* App;
