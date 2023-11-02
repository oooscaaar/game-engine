#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "glew.h"
#include <fstream>
#include <vector>
#include <stdio.h>


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

bool ModuleProgram::CleanUp()
{
    LOG("Quitting Module Program");
    //TODO: Free all resources
    return true;
}

char* ModuleProgram::ReadShader(const char* filename)
{
    char* data = nullptr;
    FILE* file = nullptr;
    fopen_s(&file, filename, "rb");
    
    if (file)
    {
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        data = (char*)malloc(size + 1);
        fseek(file, 0, SEEK_SET);
        fread(data, 1, size, file);
        data[size] = 0;

        fclose(file);
    }

   return data;
}

unsigned ModuleProgram::CompileShader(unsigned shaderType, const char* source)
{

    unsigned shader_id = glCreateShader(shaderType);
    glShaderSource(shader_id, 1, &source, 0);
    glCompileShader(shader_id);
    int res = GL_FALSE;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
        if (len > 0)
        {
            int written = 0;
            char* info = (char*)malloc(len);
            glGetShaderInfoLog(shader_id, len, &written, info);
            LOG("Log Info: %s", info);
            free(info);
        }
    }
    return shader_id;

}

unsigned ModuleProgram::CreateProgram(unsigned vtx_shader, unsigned frg_shader)
{
    unsigned program_id = glCreateProgram();
    glAttachShader(program_id, vtx_shader);
    glAttachShader(program_id, frg_shader);
    glLinkProgram(program_id);
    int res;
    glGetProgramiv(program_id, GL_LINK_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len);
        if (len > 0)
        {
            int written = 0;
            char* info = (char*)malloc(len);
            glGetProgramInfoLog(program_id, len, &written, info);
            LOG("Program Log Info: %s", info);
            free(info);
        }
    }
    glDeleteShader(vtx_shader);
    glDeleteShader(frg_shader);
    return program_id;
}

