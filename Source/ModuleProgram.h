#pragma once
#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	bool Init();
	bool CleanUp();

	char* ReadShader(const char* filename);
	unsigned CompileShader(unsigned shaderType, const char* source);
	unsigned CreateProgram(unsigned vertexShaderFilename, unsigned fragmentShaderFilename);


	private:
		unsigned int program_id = 0;

};