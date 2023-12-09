#include "Model.h"
#include "ModuleTexture.h"
#include "ModuleProgram.h"

#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE 
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"

Model::Model()
{
}

Model::~Model()
{
}


void Model::Draw()
{
	for (const auto& mesh : meshes) {
		mesh->Draw(textures, program);
	}
}

const void Model::Load(const char* filePath)
{
	std::string error, warning;
	bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, filePath);
	if (!loadOk)
	{
		LOG("Error loading Model. %s\n", filePath, error.c_str());
	}

	//Load Materials
	if (textures.empty()) {
		for (const auto& srcMaterial : model.materials) {
			unsigned int textureId = 0;
			if (srcMaterial.pbrMetallicRoughness.baseColorTexture.index >= 0) {
				const tinygltf::Texture& texture = model.textures[srcMaterial.pbrMetallicRoughness.baseColorTexture.index];
				const tinygltf::Image& image = model.images[texture.source];
				textureId = (App->texture->Load(image.uri, filePath));
			}
			textures.push_back(textureId);
		}
	}

	//Load Mesh
	for (const auto& srcMesh : model.meshes) {
		for (const auto& primitive : srcMesh.primitives) {
			Mesh* mesh = new Mesh;
			mesh->Load(model, srcMesh, primitive);	
			meshes.push_back(mesh);
		}
	}

	//Create Program
	unsigned vtx_shader = App->program->CompileShader(GL_VERTEX_SHADER, App->program->ReadShader("../Source/Shaders/assignment.vert"));
	unsigned frg_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->ReadShader("../Source/Shaders/assignment.frag"));
	program = App->program->CreateProgram(vtx_shader, frg_shader);
}

//TODO Delete meshes
//for (auto mesh : meshes)
//delete(mesh);
//meshes.clear();


//TODO Delete textures
//for (auto texture : textures)
//App->texture->Delete(texture);
//textures.clear();
