#pragma once
#include "Module.h"

class ModuleTimer : public Module
{
public:
    ModuleTimer();
    ~ModuleTimer();
    bool Init();
    update_status PreUpdate();
    bool CleanUp();
    const float GetDeltaTime() const;

private:
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
};

