#pragma once
#include "Application.h"
#include "Globals.h"
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE 
#include "tiny_gltf.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	void const Draw(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive, const std::vector<unsigned>& textures);


private:
	unsigned vbo = 0;
	unsigned vao = 0;
	unsigned ebo = 0;
	unsigned program = 0;

	void const LoadPositions(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void const LoadTextureCoordinates(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void const LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void const CreateVBO();
	void const CreateVAO();
	void const CreateProgram();
	void const Render(const std::vector<unsigned>& textures);

	unsigned int numberOfVertices;
	unsigned int numberOfIndices;

};

