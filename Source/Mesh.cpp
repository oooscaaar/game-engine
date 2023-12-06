#include "Mesh.h"
#include "SDL.h"
#include "glew.h"
#include "Math/float3.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void const Mesh::Draw(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive, const std::vector<unsigned>& textures) {

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	LoadEBO(model, mesh, primitive);
	SetNumberOfVertices(model, mesh, primitive);
	CreateVAO();

}

void const Mesh::LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive) {

	if (primitive.indices >= 0)
	{
		const tinygltf::Accessor& indAcc = model.accessors[primitive.indices];
		const tinygltf::BufferView& indView = model.bufferViews[indAcc.bufferView];
		const unsigned char* buffer = &(model.buffers[indView.buffer].data[indAcc.byteOffset +
			indView.byteOffset]);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indAcc.count, nullptr, GL_STATIC_DRAW);

		unsigned int* ptr = reinterpret_cast<unsigned int*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));

		if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT)
		{
			const uint32_t* bufferInd = reinterpret_cast<const uint32_t*>(buffer);
			for (uint32_t i = 0; i < (primitive.indices+1) ; ++i) ptr[i] = bufferInd[i];
		}
		/* TODO indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT*/
		/* TODO indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE*/
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}

}

void Mesh::SetNumberOfVertices(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive) {
	const auto& itPos = primitive.attributes.find("POSITION");
	if (itPos != primitive.attributes.end())
	{
		const tinygltf::Accessor& posAcc = model.accessors[itPos->second];
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		numberOfVertices = posAcc.count;
	}
}



void const Mesh::Load(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive){

	const auto& itPos = primitive.attributes.find("POSITION");

	if (itPos != primitive.attributes.end())
	{
		const tinygltf::Accessor& posAcc = model.accessors[itPos->second];
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
		const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
		const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);


		
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * posAcc.count, nullptr, GL_STATIC_DRAW);



		float3* ptr = reinterpret_cast<float3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		for (size_t i = 0; i < posAcc.count; ++i)
		{
			ptr[i] = *reinterpret_cast<const float3*>(bufferPos);
			bufferPos += posView.byteStride;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);

		glUseProgram(program);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, posAcc.count);
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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * numberOfVertices));

	glBindVertexArray(0);
}




void const Mesh::render() {

}






// THIS IS A WORKING TRIANGLE

//float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
//glGenBuffers(1, &vbo);
//glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
//glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
//glEnableVertexAttribArray(0);
//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//// Create program
//unsigned vtx_shader = App->program->CompileShader(GL_VERTEX_SHADER, App->program->ReadShader("../Source/Shaders/assignment.vert"));
//unsigned frg_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->ReadShader("../Source/Shaders/assignment.frag"));
//program = App->program->CreateProgram(vtx_shader, frg_shader);
//
//glUseProgram(program);
//
//glUniformMatrix4fv(0, 1, GL_TRUE, &(float4x4::FromTRS(float3(0.0f, 0.0f, -0.5f), float3x3::RotateZ(0), float3(1.0f, 1.0f, 1.0f)))[0][0]);
//glUniformMatrix4fv(1, 1, GL_TRUE, &(App->camera->GetViewMatrix())[0][0]);
//glUniformMatrix4fv(2, 1, GL_TRUE, &(App->camera->GetProjectionMatrix())[0][0]);
//
//// Draw triangle
//glDrawArrays(GL_TRIANGLES, 0, 3);
