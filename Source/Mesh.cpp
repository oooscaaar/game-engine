#include "Mesh.h"
#include "SDL.h"
#include "glew.h"
#include "Math/float3.h"


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::Load(const char* filePath)
{

	tinygltf::TinyGLTF gltfContext;
	tinygltf::Model model;
	std::string error, warning;
	LOG("Loading Model...\n");
	bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, filePath);
	if (!loadOk)
	{
		LOG("Error loading Model. %s\n", *filePath, error.c_str());
	}

	//LOG("Model %s LOADED.\n", *filePath);

	//Load Mesh
	for (const auto& srcMesh : model.meshes)
	{
		for (const auto& primitive : srcMesh.primitives)
		{
			Mesh* mesh = new Mesh;
			mesh->Load(model, srcMesh, primitive);
		}
	}
}

void Mesh::Load(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive){

	const auto& itPos = primitive.attributes.find("POSITION");

	if (itPos != primitive.attributes.end())
	{
		//const tinygltf::Accessor& posAcc = model.accessors[itPos->second];
		//SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
		//SDL_assert(posAcc.componentType == GL_FLOAT);
		//const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
		//const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
		//const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);

		//glGenBuffers(1, &vbo);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * posAcc.count, bufferPos, GL_STATIC_DRAW);

		const tinygltf::Accessor& posAcc = model.accessors[itPos->second];
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
		const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
		const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);
		glGenBuffers(1, &vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * posAcc.count, nullptr, GL_STATIC_DRAW);
		float3* ptr = reinterpret_cast<float3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		for (size_t i = 0; i < posAcc.count; ++i)
		{
			ptr[i] = *reinterpret_cast<const float3*>(bufferPos);
			bufferPos += posView.byteStride;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}

void const Mesh::CreateVAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
	//TODO: Use the real number of vertices
	const int numVertices = 6;
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * numVertices));

	glBindVertexArray(0);
}

void const Mesh::Draw()
{
	//TODO: use the real number of indices
	const int numIndices = 6;

	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);
}
