#pragma once
#include "Application.h"
#include "ModuleTimer.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleOpenGL.h"
#include "ModuleDebugDraw.h"
#include "ModuleLoader.h"
#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "ModuleRenderAssignment.h"

using namespace std;

Application::Application()
{
	modules.push_back(timer = new ModuleTimer());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(render = new ModuleOpenGL());
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(input = new ModuleInput());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(debugDraw = new ModuleDebugDraw());
	modules.push_back(texture = new ModuleTexture());
	modules.push_back(moduleLoader = new ModuleLoader());
	modules.push_back(renderAssignment= new ModuleRenderAssignment());
}

Application::~Application()
{
	for(list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}
