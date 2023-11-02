#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"

ModuleProgram::ModuleProgram()
{}

ModuleProgram::~ModuleProgram()
{}

bool ModuleProgram::Init()
{
    LOG("Initialize Module Program");
    bool ret = true;

    // TODO: Check initialization and return false if errors
    if (false)
    {
        ret = false;
    }

    return ret;
}

update_status ModuleProgram::PreUpdate()
{
    return UPDATE_CONTINUE;
}

update_status ModuleProgram::Update()
{
    return UPDATE_CONTINUE;
}

update_status ModuleProgram::PostUpdate()
{
    return UPDATE_CONTINUE;
}

bool ModuleProgram::CleanUp()
{
    LOG("Quitting Module Program");
    //TODO: Free all resources
    return true;
}
