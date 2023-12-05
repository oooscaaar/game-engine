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

	void Load(const char* path);
	void Load(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void const Draw();
	void setProgram(unsigned program);

private:
	unsigned vbo;
	unsigned vao;
	unsigned ebo;
	unsigned program;
	void const CreateVAO(unsigned const int numberOfVertices);


};

