#include "Mesh.h"
#include "SDL.h"
#include "glew.h"
#include "Math/float3.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "Math/float4x4.h"


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void const Mesh::Load(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive) {

	LoadPositions(model, mesh, primitive);

	LoadTextureCoordinates(model, mesh, primitive);

	LoadEBO(model, mesh, primitive);
		
	CreateVAO();

}

void const Mesh::Draw(const std::vector<unsigned>& textures, const unsigned& program) {
	Render(textures, program);
}

void const Mesh::LoadPositions(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive) {

	const auto& itPos = primitive.attributes.find("POSITION");
	if (itPos != primitive.attributes.end())
	{
		const tinygltf::Accessor& posAcc = model.accessors[itPos->second];
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
		const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
		const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(float3) + sizeof(float2)) * posAcc.count, nullptr, GL_STATIC_DRAW);

		numberOfVertices = posAcc.count;
		float3* ptr = reinterpret_cast<float3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		for (size_t i = 0; i < posAcc.count; ++i)
		{
			ptr[i] = *reinterpret_cast<const float3*>(bufferPos);
			if (posView.byteStride == 0) {
				bufferPos += sizeof(float)*3;
			}
			else {
				bufferPos += posView.byteStride;
			}
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}

void const Mesh::LoadTextureCoordinates(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive) {

	const auto& itCoord = primitive.attributes.find("TEXCOORD_0");
	if (itCoord != primitive.attributes.end())
	{
		const tinygltf::Accessor& posAcc = model.accessors[itCoord->second];
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC2);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
		const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
		const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		float2* ptr = reinterpret_cast<float2*>(reinterpret_cast<char*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY)) + sizeof(float) * 3 * numberOfVertices);
		for (size_t i = 0; i < posAcc.count; ++i)
		{
			ptr[i] = *reinterpret_cast<const float2*>(bufferPos);
			if (posView.byteStride == 0) {
				bufferPos += sizeof(float) * 2;
			}
			else {
				bufferPos += posView.byteStride;
			}
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}

void const Mesh::LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive) {

	if (primitive.indices >= 0)
	{
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		numberOfIndices = model.accessors[primitive.indices].count;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numberOfIndices, nullptr, GL_STATIC_DRAW);
		unsigned int* ptr = reinterpret_cast<unsigned int*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));

		const tinygltf::Accessor& indAcc = model.accessors[primitive.indices];
		const tinygltf::BufferView& indView = model.bufferViews[indAcc.bufferView];
		const unsigned char* buffer = &(model.buffers[indView.buffer].data[indAcc.byteOffset +
			indView.byteOffset]);

		if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT)
		{
			const uint32_t* bufferInd = reinterpret_cast<const uint32_t*>(buffer);
			for (uint32_t i = 0; i < numberOfIndices; ++i) ptr[i] = bufferInd[i];
		}

		if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT) {
			const uint16_t* bufferInd = reinterpret_cast<const uint16_t*>(buffer);
			for (uint16_t i = 0; i < numberOfIndices; ++i) {
				ptr[i] = bufferInd[i];
			}
		}

		if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE) {
			const uint8_t* bufferInd = reinterpret_cast<const uint8_t*>(buffer);
			for (uint8_t i = 0; i < numberOfIndices; ++i) {
				ptr[i] = bufferInd[i];
			}
		}

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}

}


void const Mesh::CreateVAO()
{
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)(sizeof(float) * 3 * numberOfVertices));

	glBindVertexArray(0);
}



void const Mesh::Render(const std::vector<unsigned>& textures, const unsigned &program)
{
	glUseProgram(program);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	//TODO: Get the texture from the material -> meshes.primitives[n].material
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	glUniformMatrix4fv(0, 1, GL_TRUE, &(float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f), float3x3::RotateZ(0), float3(50.0f, 50.0f, 50.0f))[0][0]));
	glUniformMatrix4fv(1, 1, GL_TRUE, &(App->camera->GetViewMatrix())[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &(App->camera->GetProjectionMatrix())[0][0]);
	glUniform1i(glGetUniformLocation(program, "diffuse"), 0);

	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}