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
		mesh->Draw(textures, program, matrix);
	}
}

bool Model::Load(const char* filePath)
{
	std::string error, warning;
	tinygltf::TinyGLTF gltfContext;
	tinygltf::Model model;
	bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, filePath);
	if (!loadOk)
	{
		LOG("Error loading Model. %s\n", filePath, error.c_str());
		return false;
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

	//Load Meshes
	for (const auto& srcMesh : model.meshes) {
		for (const auto& primitive : srcMesh.primitives) {
			Mesh* mesh = new Mesh;
			mesh->Load(model, srcMesh, primitive);	
			meshes.push_back(mesh);
		}
	}

	//Create shader program
	unsigned vtx_shader = App->program->CompileShader(GL_VERTEX_SHADER, App->program->ReadShader("./Shaders/assignment.vert"));
	unsigned frg_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->ReadShader("./Shaders/assignment.frag"));
	program = App->program->CreateProgram(vtx_shader, frg_shader);

	return true;
}

//Cleanup meshes and textures STL containers
void Model::Clear()
{
	for (auto mesh : meshes)
		delete(mesh);
	meshes.clear();
	
	for (auto texture : textures)
		App->texture->Delete(texture);
	textures.clear();

}

