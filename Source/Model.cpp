#include "Model.h"
#include "ModuleTexture.h"
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE 
#include "tiny_gltf.h"

Model::Model()
{

}

Model::~Model()
{
}


void Model::Draw(const char* filePath)
{
		tinygltf::TinyGLTF gltfContext;
		tinygltf::Model model;
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
					textureId = (App->texture->Load(image.uri));
				}
				textures.push_back(textureId);
			}
		}

	
		//Load Mesh
		for (const auto& srcMesh : model.meshes) {
			for (const auto& primitive : srcMesh.primitives) {
				Mesh* mesh = new Mesh;
				mesh->Draw(model, srcMesh, primitive, textures);
				meshes.push_back(mesh);
			}
		}


		//TODO Delete meshes
		for (auto mesh : meshes)
			delete(mesh);
		meshes.clear();

		//TODO Delete textures
		for (auto texture : textures)
			App->texture->Delete(texture);
			textures.clear();
}
