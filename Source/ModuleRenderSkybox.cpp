#include "ModuleRenderSkybox.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "glew.h"
#include <string>
#include <filesystem>
#include<list>

ModuleRenderSkybox::ModuleRenderSkybox()
{
}

ModuleRenderSkybox::~ModuleRenderSkybox()
{
}

bool ModuleRenderSkybox::Init()
{
	LOG("Intitialize Module Render Skybox\n");

    LoadCubeMap();

    float skyboxVertices[] = {
         //positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };


    // skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned vtx_shader = App->program->CompileShader(GL_VERTEX_SHADER, App->program->ReadShader("./Shaders/skybox.vert"));
    unsigned frg_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->ReadShader("./Shaders/skybox.frag"));
    program = App->program->CreateProgram(vtx_shader, frg_shader);



    // skybox cube
    

    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

    


    return true;
}

update_status ModuleRenderSkybox::PreUpdate()
{
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBindVertexArray(skyboxVAO);

    //glUniformMatrix4fv(0, 1, GL_TRUE, (const float*)&model);
    //glUniformMatrix4fv(1, 1, GL_TRUE, &(App->camera->GetViewMatrix())[0][0]);
    //glUniformMatrix4fv(2, 1, GL_TRUE, &(App->camera->GetProjectionMatrix())[0][0]);

    proj = App->camera->GetProjectionMatrix();
    model = float4x4::FromTRS(float3(0.0f, 0.0f, -0.5f), float3x3::RotateZ(0), float3(1.0f, 1.0f, 1.0f));
    view = App->camera->GetViewMatrix();

    glUseProgram(program);

    glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
    glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
    glUniformMatrix4fv(2, 1, GL_TRUE, &proj[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);



    //glUseProgram(program);

    //glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    //glBindVertexArray(skyboxVAO);



    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, texture);

    //glUniformMatrix4fv(0, 1, GL_TRUE, (const float*)&modelMatrix);

    //glUniformMatrix4fv(1, 1, GL_TRUE, &(App->camera->GetViewMatrix())[0][0]);
    //glUniformMatrix4fv(2, 1, GL_TRUE, &(App->camera->GetProjectionMatrix())[0][0]);
    //glUniform1i(glGetUniformLocation(program, "diffuse"), 0);

    //glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, nullptr);

    //glBindVertexArray(0);



    //glDepthFunc(GL_LESS);
	return update_status::UPDATE_CONTINUE;
}

bool ModuleRenderSkybox::CleanUp()
{
	return true;
}

unsigned ModuleRenderSkybox::LoadCubeMap()
{
    DirectX::ScratchImage image;

    HRESULT res = DirectX::LoadFromDDSFile(L"../Game/Textures/cubemap.dds", DirectX::DDS_FLAGS_NONE, nullptr, image);

    if (res == S_OK)
    {
        const DirectX::TexMetadata& metadata = image.GetMetadata();

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

        for (uint32_t i = 0; i < metadata.arraySize; ++i)
        {
            const DirectX::Image* face = image.GetImage(0, i, 0);

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, face->width, face->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, face->pixels);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return texture;
    }

    //TODO: Manage error

}
