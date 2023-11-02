#pragma once
#include "Module.h"
#include "Globals.h"
#include <iostream>

typedef unsigned __int8 Uint8;

class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	bool Init();
	bool CleanUp();

	unsigned CreateProgram(unsigned vertexShaderFilename, unsigned fragmentShaderFilename);


private:

	char* ReadShader(const char* filename);
	unsigned CompileShader(unsigned shaderType, const char* source, const char* shaderName);

};