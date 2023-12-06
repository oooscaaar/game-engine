#include "Model.h"
#include "ModuleTexture.h"
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE 
#include "tiny_gltf.h"

Model::Model()
{
	std::list<Mesh*> meshes;
	std::vector<unsigned> textures;
}

Model::~Model()
{
}


void Model::Draw(const char* filePath)
{
		tinygltf::TinyGLTF gltfContext;
		tinygltf::Model model;
		std::string error, warning;
		LOG("Loading Model...\n");
		bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, filePath);
		if (!loadOk)
		{
			LOG("Error loading Model. %s\n", filePath, error.c_str());
		}
		else {
			LOG("Model %s LOADED.\n", filePath);
		}

		//Load Materials
		std::vector<unsigned> textures;
			for (const auto& srcMaterial : model.materials)
			{
				unsigned int textureId = 0;
				if (srcMaterial.pbrMetallicRoughness.baseColorTexture.index >= 0)
				{
					const tinygltf::Texture& texture = model.textures[srcMaterial.pbrMetallicRoughness.baseColorTexture.index];
					const tinygltf::Image& image = model.images[texture.source];
					//TODO: Use real texture uri

					textureId = (App->texture->Load(image.uri));
				}
				textures.push_back(textureId);
			}
	
		//Load Mesh
		for (const auto& srcMesh : model.meshes)
		{
			for (const auto& primitive : srcMesh.primitives)
			{
				Mesh* mesh = new Mesh;
				mesh->Draw(model, srcMesh, primitive, textures);
				//Model::meshes.push_back(mesh);
			}
		}

}
//
//void Mesh::Load(const char* filePath)
//{
//
//	tinygltf::TinyGLTF gltfContext;
//	tinygltf::Model model;
//	std::string error, warning;
//	LOG("Loading Model...\n");
//	bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, filePath);
//	if (!loadOk)
//	{
//		LOG("Error loading Model. %s\n", *filePath, error.c_str());
//	}
//
//	//LOG("Model %s LOADED.\n", *filePath);
//
//	//Load Mesh
//	for (const auto& srcMesh : model.meshes)
//	{
//		for (const auto& primitive : srcMesh.primitives)
//		{
//			Mesh* mesh = new Mesh;
//			//mesh->Load(model, srcMesh, primitive);
//		}
//	}
//
//
//
//}