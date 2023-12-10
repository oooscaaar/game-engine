#pragma once
#include "Application.h"
#include "Mesh.h"
#include "Math/float4x4.h"



class Model
{
	public:

		Model();
		~Model();
		void Draw();
		bool Load(const char* filePath);
		void Clear();
		const std::vector<Mesh*>& GetMeshes() const { return meshes; }


	private:
		std::vector<Mesh*> meshes;
		std::vector<unsigned int> textures;
		unsigned program = 0;
		float4x4 matrix = float4x4::identity;
};

