#pragma once
#include "Module.h"
#include "Model.h"
class ModuleLoader :
    public Module
{
    public:
	ModuleLoader();
	~ModuleLoader();
	bool Init();
	update_status PreUpdate();
	bool CleanUp();
	void LoadModel(const char* filePath);
	Model* GetModel() const { return model; }

private:
	Model* model = nullptr;
};

