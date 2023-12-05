#pragma once
#include "Module.h"
#include "Mesh.h"

#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE 
#include "tiny_gltf.h"

class ModuleModel :
    public Module
{

public:
    ModuleModel();
	~ModuleModel();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	//void Load(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	//void const Draw();
	void LoadModel(const char* filePath);

private:
	tinygltf::TinyGLTF gltfContext;
	tinygltf::Model model;
	unsigned vbo;
	unsigned program;
	unsigned int verticesCount;
};

