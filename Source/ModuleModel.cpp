#include "ModuleModel.h"
#include "SDL.h"
#include "glew.h"
#include "Math/float3.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "Application.h"

ModuleModel::ModuleModel()
{
}

ModuleModel::~ModuleModel()
{
}

bool ModuleModel::Init()
{
	//CreateTriangleVBO
	//float buffer_data[] =
	//{
	//	-1.0f, -1.0f, 0.0f, // ← Vertex 0 position
	//	1.0f, 1.0f, 0.0f, // ← Vertex 1 position
	//	-1.0f, 1.0f, 0.0f, // ← Vertex 2 position
	//	-1.0f, -1.0f, 0.0f, // ← Vertex 3 position
	//	1.0f, -1.0f, 0.0f, // ← Vertex 4 position
	//	1.0f, 1.0f, 0.0f, // ← Vertex 5 position
	//	0.0f, 1.0f, // ← Vertex 0 Texture coordinates
	//	1.0f, 0.0f, // ← Vertex 1 Texture coordinates
	//	0.0f, 0.0f, // ← Vertex 2 Texture coordinates
	//	0.0f, 1.0f, // ← Vertex 3 Texture coordinates
	//	1.0f, 1.0f, // ← Vertex 4 Texture coordinates
	//	1.0f, 0.0f // ← Vertex 5 Texture coordinates
	//};

	LoadModel("../Game/Models/BakerHouse/BakerHouse.gltf");





	const auto& itPos = model.meshes[0].primitives[0].attributes.find("POSITION");

	if (itPos != model.meshes[0].primitives[0].attributes.end())
	{
		const tinygltf::Accessor& posAcc = model.accessors[itPos->second];
		SDL_assert(posAcc.type == TINYGLTF_TYPE_VEC3);
		SDL_assert(posAcc.componentType == GL_FLOAT);
		const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
		const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
		const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);

		verticesCount = posAcc.count;

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * posAcc.count, bufferPos, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

		// Create program
		unsigned vtx_shader = App->program->CompileShader(GL_VERTEX_SHADER, App->program->ReadShader("../Source/Shaders/assignment.vert"));
		unsigned frg_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, App->program->ReadShader("../Source/Shaders/assignment.frag"));
		program = (App->program->CreateProgram(vtx_shader, frg_shader));

		


		//float3* ptr = reinterpret_cast<float3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
		//for (size_t i = 0; i < posAcc.count; ++i)
		//{
		//	ptr[i] = *reinterpret_cast<const float3*>(bufferPos);
		//	bufferPos += posView.byteStride;
		//}
		//glUnmapBuffer(GL_ARRAY_BUFFER);




	}

	return true;
}

update_status ModuleModel::PreUpdate()
{

	float4x4 modelMatrix = (float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f), float3x3::RotateZ(0), float3(10.0f, 10.0f, 10.0f)));
	float4x4 viewMatrix = App->camera->GetViewMatrix();
	float4x4 projectionMatrix = App->camera->GetProjectionMatrix();

	// Draw triangle
	glUseProgram(program);

	glUniformMatrix4fv(0, 1, GL_TRUE, &modelMatrix[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &viewMatrix[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &projectionMatrix[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, verticesCount);

	return UPDATE_CONTINUE;
}

update_status ModuleModel::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleModel::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleModel::CleanUp()
{
	glDeleteBuffers(1, &vbo);
	return true;
}

void ModuleModel::LoadModel(const char* filePath) {
	std::string error, warning;
	LOG("Loading Model...\n");
	bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, filePath);
	if (!loadOk)
	{
		LOG("Error loading Model. %s\n", *filePath, error.c_str());
	}

	//LOG("Model %s LOADED.\n", *filePath);

	//for (const auto& srcMesh : model.meshes)
	//{
	//	for (const auto& primitive : srcMesh.primitives)
	//	{
	//		//Mesh* mesh = new Mesh;
	//		//esh->Load(model, srcMesh, primitive);
	//	}
	//}
}
